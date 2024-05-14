#include "position.h"

inline Move randomMove(Position& pos) {
    Move moves[MAX_MOVES];
    int count = pos.generate_moves(moves);
    
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
        cout << i << " " << score << endl;
        if (bestScore < score) {
            bestScore = score;
            best = i;
        }
    }
    
    return moves[best];
}