#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <set>
#include <climits>
#include <utility>
#include <cstdlib>

#define SORTING true
#define SORT_DEPTH 0

using namespace std;
 
static const uint64_t MASKS[8] = {
    0x7F7F7F7F7F7F7F7F, // mask for right shift
    0x007F7F7F7F7F7F7F, // mask for down-right shift
    0xFFFFFFFFFFFFFFFF, // mask for down shift
    0x00FEFEFEFEFEFEFE, // mask for down-left shift
    0xFEFEFEFEFEFEFEFE, // mask for left shift
    0xFEFEFEFEFEFEFE00, // mask for up-left shift
    0xFFFFFFFFFFFFFFFF, // mask for up shift
    0x7F7F7F7F7F7F7F00 // mask for up-right shift
};

static const uint64_t LSHIFTS[8] = {
    0, // r 
    0, // dr
    0, // d
    0, // dl
    1, // l
    9, // ul
    8, // u
    7  // ur
};

static const uint64_t RSHIFTS[8] = {
    1, // r
    9, // dr
    8, // d
    7, // dl
    0, // l
    0, // ul
    0, // u
    0  // ur
};

class Reversi{
    public:
        std::array<uint64_t, 2> board;
        Reversi(std::array<uint64_t, 2> board){
            this->board = board;
        }
        Reversi() {
            this->board = {0x0000001008000000, 0x0000000810000000};
        }
        uint64_t allMoves(uint64_t player, uint64_t opp);
        uint64_t getMoves(Reversi R, bool player);
        Reversi makeMove(Reversi R, int idx, bool player);
        void printBoard(Reversi R);
        int result(Reversi R);
        int stability(Reversi R, bool player);
        int heuristic(Reversi R, uint64_t playerMoves, uint64_t oppMoves, bool player);
        pair<int, int> alphaBetaMax(Reversi R, int depth, int alpha, int beta, bool player);
        int randomMove(Reversi R, uint64_t moves, bool player);
        int bestMove(Reversi R, bool player, int depth);
};

uint64_t Reversi::allMoves(uint64_t player, uint64_t opp){
    uint64_t empty = ~(player | opp);
    uint64_t moves = 0;
    uint64_t tmp;
    for(int i = 0; i < 4; i++){ // right
        tmp = ((player >> RSHIFTS[i]) & MASKS[i]) & opp;

        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & opp;

        // cerr << "TMP " << tmp << " empty " << empty << endl;
        moves |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & empty;
    }
    for(int i = 4; i < 8; i++){ // left
        tmp = ((player << LSHIFTS[i]) & MASKS[i]) & opp;

        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;

        moves |= ((tmp << LSHIFTS[i]) & MASKS[i]) & empty;
    }
    return moves;
}

uint64_t Reversi::getMoves(Reversi R, bool player){
    uint64_t moves = allMoves(R.board[player], R.board[!player]);
    return moves;
}

Reversi Reversi::makeMove(Reversi R, int idx, bool player){
    if (idx == -1){
        return R;
    }
    uint64_t move = 1ULL << idx;
    uint64_t newP = R.board[player] | move;
    uint64_t fliped = 0;
    uint64_t tmp;
    uint64_t last;

    for (int i = 0; i < 4; i++){
        tmp = ((move >> RSHIFTS[i]) & MASKS[i]) & R.board[!player];

        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & R.board[!player];
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & R.board[!player];
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & R.board[!player];
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & R.board[!player];
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & R.board[!player];

        last = ((tmp >> RSHIFTS[i]) & MASKS[i]) & newP;
        fliped |= (last ? tmp : 0);
    }

    for (int i = 4; i < 8; i++){
        tmp = ((move << LSHIFTS[i]) & MASKS[i]) & R.board[!player];

        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & R.board[!player];
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & R.board[!player];
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & R.board[!player];
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & R.board[!player];
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & R.board[!player];

        last = ((tmp << LSHIFTS[i]) & MASKS[i]) & newP;
        fliped |= (last ? tmp : 0);
    }

    Reversi newR = Reversi();
    newR.board[player] = newP ^ fliped;
    newR.board[!player] = board[!player] ^ fliped;

    return newR;
}

void Reversi::printBoard(Reversi R){
    for(int i = 0; i < 64; i++){
        if (i % 8 == 0 && i != 0){
            cerr << endl;
        }
        if (R.board[0] & (1ULL << i)){
            cerr << "X";
        } else if (R.board[1] & (1ULL << i)){
            cerr << "O";
        } else {
            cerr << ".";
        }
    }
    cerr << endl;
}

int Reversi::result(Reversi R){
    return __popcount(R.board[1]) - __popcount(R.board[0]);
}

int Reversi::stability(Reversi R, bool player){
    uint64_t empty = ~(R.board[player] | R.board[!player]);
    uint64_t playerBorder = 0;
    uint64_t oppBorder = 0;
    uint64_t tmp;
    for(int i = 0; i < 4; i++){
        tmp = (empty >> RSHIFTS[i]);
        playerBorder |= tmp & R.board[player];
        oppBorder |= tmp & R.board[!player];
    }
    for(int i = 4; i < 8; i++){
        tmp = (empty << LSHIFTS[i]);
        playerBorder |= tmp & R.board[player];
        oppBorder |= tmp & R.board[!player];
    }

    return __popcount(playerBorder) - __popcount(oppBorder);
}

int Reversi::heuristic(Reversi R, uint64_t playerMoves, uint64_t oppMoves, bool player){
    int balance = __popcount(R.board[player]) - __popcount(R.board[!player]);
    if (playerMoves == 0 && oppMoves == 0){
        return balance << 10;
    }
    int mobility = __popcount(playerMoves) - __popcount(oppMoves);
    int corners = (__popcount(R.board[player] & 0x8100000000000081ULL) - __popcount(R.board[!player] & 0x8100000000000081ULL));
    
    int score = balance * 0; 
    score += mobility << 1;
    score += corners << 4;
    score += stability(R, player) << 1;
    return score;
}

pair<int, int> Reversi::alphaBetaMax(Reversi R, int depth, int alpha, int beta, bool player){
    int value = INT_MIN;
    int bestMove = -1;
    uint64_t playerMoves = getMoves(R, player);
    uint64_t oppMoves = getMoves(R, !player);
    if (depth < 1 || (playerMoves == 0 && oppMoves == 0)){
        return {heuristic(R, playerMoves, oppMoves, player), bestMove};
    }
    if (playerMoves == 0 && oppMoves != 0){
        return {alphaBetaMax(R, depth - 1, -beta, -alpha, !player).first, bestMove};
    }

    vector<pair<int, int>> moves;
    for(int i = 0; i < 64; i++){
        if(playerMoves & (1ULL << i)){
            auto tmpR = makeMove(R, i, player);
            moves.push_back({i, heuristic(tmpR, playerMoves, oppMoves, player)});
        }
    }

    if (SORTING && depth > SORT_DEPTH) {
        sort(moves.begin(), moves.end(), [&](pair<int, int> a, pair<int, int> b) {
            // return (player ? (a.second > b.second) : (a.second < b.second));
            return (a.second > b.second);
        });
    }

    for (auto move : moves) {
        Reversi newR = makeMove(R, move.first, player);
        pair<int, int> result = alphaBetaMax(newR, depth - 1, -beta, -alpha, !player);
        result.first = -result.first;
        
        // if (depth == 2) {
        //     cerr << "3 layer: " << result.first << endl;
        //     result = alphaBetaMax(newR, 0, -beta, -alpha, !player);
        //     result.first = -result.first;
        //     cerr << "2 layer: " << result.first << endl;
        // }
        
        if (bestMove == -1) {
            bestMove = move.first;
        }
        if (result.first > value) {
            // if (depth == 5) {
            //     cerr << "new best " << result.first << endl;
            // }
            value = result.first;
            bestMove = move.first;
        }
        // cerr << "v " << value << " h " << move.second << endl;
        if (value >= beta && SORTING && depth > SORT_DEPTH) {
            // break;
        }
        alpha = max(alpha, value);
    }
    // cerr << "player " << player << " score " << value << " move " << bestMove << " depth " << depth << endl;
    return {value, bestMove};
}

int Reversi::randomMove(Reversi R, uint64_t moves, bool player){
    vector<int> possibleMoves;
    for(int i = 0; i < 64; i++){
        if(moves & (1ULL << i)){
            possibleMoves.push_back(i);
        }
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(possibleMoves.begin(), possibleMoves.end(), g);
    return possibleMoves[0];
}

int Reversi::bestMove(Reversi R, bool player, int depth){
    uint64_t moves = getMoves(R, player);
    // cerr << "MY moves " << moves << endl;
    if (moves == 0){
        return -1;
    }
    return alphaBetaMax(R, depth, INT_MIN, INT_MAX, player).second;
}