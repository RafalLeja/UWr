#include "position.h"
#include <algorithm>
#include <cmath>
#include <climits>

static uint32_t const LOCATION_WEIGHTS[2][64] = {
    {
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 3, 2, 2, 2,
        2, 2, 3, 8, 3, 2, 2,
        2, 3, 8, 10000, 8, 3, 2, 0
    },
    {
        2, 3, 8, 10000, 8, 3, 2,
        2, 2, 3, 8, 3, 2, 2,
        2, 2, 2, 3, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0
    }
};

inline Move randomMove(Position& pos) {
    Move moves[MAX_MOVES];
    int count = pos.generate_moves(moves);
    
    if (count == 0) {
        // cout << "No moves available" << endl;
        return Move();
    }
    return moves[rand() % count];
}

int simulate(Position& pos) {
    while (!pos.is_won()) {
        Move m = randomMove(pos);
        pos.do_move(m);
    }
    
    return pos.is_white_turn() ? -1 : 1;
}

Move simSearch(Position& pos, int games) {    
    Move moves[MAX_MOVES];
    int count = pos.generate_moves(moves);
        
    bool color = pos.is_white_turn();
    Position next;
    Position tmp;

    int best = 0;
    int bestScore = -(games << 2);
    for (int i = 0; i < count; i++) {
        next = pos;
        next.do_move(moves[i]);
        
        int score = 0;
        for (int j = 0; j < games; j++) {
            tmp = next;
            int a = simulate(tmp);
            score += a * color;
            score -= a * !color;
        }
        // cout << i << " " << score << endl;
        if (bestScore < score) {
            bestScore = score;
            best = i;
        }
    }
    
    return moves[best];
}

int heuristic(Position& pos) {
    int score = 0;
    int strength_score_w = 0;
    int strength_score_b = 0;
    int piece;

    for (int i = 0; i < 16; i++) {
        piece = pos.piece(i);

        strength_score_b += strength(piece) * (i % 2) * LOCATION_WEIGHTS[0][piece];
        strength_score_w += strength(piece) * !(i % 2) * LOCATION_WEIGHTS[1][piece];
    }

    return strength_score_w - strength_score_b;
}

pair<Move, int> negamax(Position& pos, int depth, int alpha, int beta, int color) {
    if (depth == 0 || pos.is_won()) {
        return {Move(), color * heuristic(pos)};
    }

    Move moves[MAX_MOVES];
    int count = pos.generate_moves(moves);
    
    Move bestMove;
    int bestScore = alpha;
    int score;
    Position next;
    for (int i = 0; i < count; i++) {
        next = pos;
        next.do_move(moves[i]);
        
        score = -negamax(next, depth - 1, -beta, -bestScore, -color).second;
        if (score > bestScore) {
            bestScore = score;
            bestMove = moves[i];
        }
        alpha = max(alpha, bestScore);
        if (alpha >= beta) {
            break;
        }
    }
    
    // cout << "depth " << depth << " color " << color << " score " << bestScore << endl;
    return {bestMove, bestScore};
}

Move bestMove(Position& pos, int depth) {
    return negamax(pos, depth, INT_MIN, INT_MAX, pos.is_white_turn() ? 1 : -1).first;
}