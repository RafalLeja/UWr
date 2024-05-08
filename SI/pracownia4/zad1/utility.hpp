#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <set>
#include <climits>
#include <utility>
#include <cstdlib>

using namespace std;

enum Player{
    WHITE = 1,
    BLACK = 0
};  

typedef array<uint64_t, 2> Board;

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

uint64_t allMoves(uint64_t player, uint64_t opp);
uint64_t getMoves(Board board, bool player);
array<uint64_t, 2> makeMove(Board board, int idx, bool player);


uint64_t allMoves(uint64_t player, uint64_t opp){
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

        moves |= empty & ((tmp >> RSHIFTS[i]) & MASKS[i]);
    }
    for(int i = 4; i < 8; i++){ // left
        tmp = ((player << LSHIFTS[i]) & MASKS[i]) & opp;

        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & opp;

        moves |= empty & ((tmp << LSHIFTS[i]) & MASKS[i]);
    }
    return moves;
}

uint64_t getMoves(Board board, bool player){
    uint64_t moves = allMoves(board[player], board[!player]);
    return moves;
}

array<uint64_t, 2> makeMove(Board board, int idx, bool player){
    if (idx == -1){
        return board;
    }
    uint64_t move = 1ULL << idx;
    uint64_t newP = board[player] | move;
    uint64_t fliped = 0;
    uint64_t tmp;
    uint64_t last;

    for (int i = 0; i < 4; i++){
        tmp = ((move >> RSHIFTS[i]) & MASKS[i]) & board[!player];

        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & board[!player];
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & board[!player];
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & board[!player];
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & board[!player];
        tmp |= ((tmp >> RSHIFTS[i]) & MASKS[i]) & board[!player];

        last = ((tmp >> RSHIFTS[i]) & MASKS[i]) & newP;
        fliped |= (last ? tmp : 0);
    }

    for (int i = 4; i < 8; i++){
        tmp = ((move << LSHIFTS[i]) & MASKS[i]) & board[!player];

        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & board[!player];
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & board[!player];
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & board[!player];
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & board[!player];
        tmp |= ((tmp << LSHIFTS[i]) & MASKS[i]) & board[!player];

        last = ((tmp << LSHIFTS[i]) & MASKS[i]) & newP;
        fliped |= (last ? tmp : 0);
    }

    Board newBoard;
    newBoard[player] = newP ^ fliped;
    newBoard[!player] = board[!player] ^ fliped;

    return newBoard;
}

