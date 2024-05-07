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

// class Board{
//     public:
//         uint64_t white = 0;
//         uint64_t black = 0;

//         Board(){
//             white = 0x0000000810000000;
//             black = 0x0000001008000000;
//         }
// };   

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
bool canBeat(const Board &board, int x, int y, int dx, int dy, bool player);
vector<pair<int, int>> getMoves(uint64_t board[2], bool player);


uint64_t allMoves(uint64_t player, uint64_t opp){
    uint64_t empty = ~(player | opp);
    uint64_t moves = 0;
    uint64_t tmp;
    for(int i = 0; i < 4; i++){ // right
        tmp = (player >> RSHIFTS[i]) & opp;

        tmp |= (tmp >> RSHIFTS[i]) & opp;
        tmp |= (tmp >> RSHIFTS[i]) & opp;
        tmp |= (tmp >> RSHIFTS[i]) & opp;
        tmp |= (tmp >> RSHIFTS[i]) & opp;
        tmp |= (tmp >> RSHIFTS[i]) & opp;

        moves |= empty & (tmp >> RSHIFTS[i]);
    }
    for(int i = 4; i < 8; i++){ // left
        tmp = (player << LSHIFTS[i]) & opp;

        tmp |= (tmp << LSHIFTS[i]) & opp;
        tmp |= (tmp << LSHIFTS[i]) & opp;
        tmp |= (tmp << LSHIFTS[i]) & opp;
        tmp |= (tmp << LSHIFTS[i]) & opp;
        tmp |= (tmp << LSHIFTS[i]) & opp;

        moves |= empty & (tmp << LSHIFTS[i]);
    }
    return moves;
}

bool canBeat(const Board &B, int x, int y, int dx, int dy, bool player){
    x += dx;
    y += dy;
    int count = 0;
    while(get(B, x, y) == ((!player) ? '#' : 'O')){
        count++;
        x += dx;
        y += dy;
    }
    return count > 0 && get(B, x, y) == (player ? '#' : 'O');
}

vector<pair<int, int>> getMoves(uint64_t board[2], bool player){
    uint64_t moves = allMoves(board[player], board[!player]);
    

    // for(int i = 0; i < 8; i++){
    //     for(int j = 0; j < 8; j++){
    //         if(board[i][j] == '.'){
    //             bool can = false;
    //             for(int dx = -1; dx <= 1; dx++){
    //                 for(int dy = -1; dy <= 1; dy++){
    //                     if(dx == 0 && dy == 0){
    //                         continue;
    //                     }
    //                     if(canBeat(board, i, j, dx, dy, player)){
    //                         can = true;
    //                     }
    //                 }
    //             }
    //             if(can){
    //                 moves.push_back({i, j});
    //             }
    //         }
    //     }
    // }
    return moves;
}


