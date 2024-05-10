#include "utility.hpp"
#include <algorithm>

#define SORTING true
#define SORT_DEPTH 2

void printBoard(Board board);
int result(Board board);
int stability(Board board, bool player);
int heuristic(Board board, uint64_t playerMoves, uint64_t oppMoves, bool player);
pair<int, int> alphaBetaMax(Board board, int depth, int alpha, int beta, bool player);
int randomMove(Board board, uint64_t moves, bool player);
int bestMove(Board board, bool player, int depth);

void printBoard(Board board){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            uint64_t pixel = (1ULL << (i * 8 + j));
            if(board[0] & pixel){
                cerr << "#";
            } else if(board[1] & pixel){
                cerr << "O";
            } else {
                cerr << ".";
            }
        }
        cerr << endl;
    }
}

int result(Board board){
    return __popcount(board[1]) - __popcount(board[0]);
}

int stability(Board board, bool player){
    uint64_t empty = ~(board[player] | board[!player]);
    uint64_t playerBorder = 0;
    uint64_t oppBorder = 0;
    uint64_t tmp;
    for(int i = 0; i < 4; i++){
        tmp = (empty >> RSHIFTS[i]);
        playerBorder |= tmp & board[player];
        oppBorder |= tmp & board[!player];
    }
    for(int i = 4; i < 8; i++){
        tmp = (empty << LSHIFTS[i]);
        playerBorder |= tmp & board[player];
        oppBorder |= tmp & board[!player];
    }

    return __popcount(playerBorder) - __popcount(oppBorder);
}

int heuristic(Board board, uint64_t playerMoves, uint64_t oppMoves, bool player){
    int balance = __popcount(board[player]) - __popcount(board[!player]);
    if (playerMoves == 0 && oppMoves == 0){
        return balance << 10;
    }
    int mobility = __popcount(playerMoves) - __popcount(oppMoves);
    int corners = (__popcount(board[player] & 0x8100000000000081ULL) - __popcount(board[!player] & 0x8100000000000081ULL));
    
    int score = balance * 0; 
    score += mobility << 1;
    score += corners << 4;
    score += stability(board, player) << 1;
    return score;
}

pair<int, int> alphaBetaMax(Board board, int depth, int alpha, int beta, bool player){
    int value = INT_MIN;
    int bestMove = -1;
    uint64_t playerMoves = getMoves(board, player);
    uint64_t oppMoves = getMoves(board, !player);
    if (depth == 0 || (playerMoves == 0 && oppMoves == 0)){
        return {heuristic(board, playerMoves, oppMoves, player), bestMove};
    }

    vector<pair<int, int>> moves;
    for(int i = 0; i < 64; i++){
        if(playerMoves & (1ULL << i)){
            auto tmpBoard = makeMove(board, i, player);
            moves.push_back({i, heuristic(tmpBoard, playerMoves, oppMoves, player)});
        }
    }

    if (SORTING && depth > SORT_DEPTH) {
        sort(moves.begin(), moves.end(), [&](pair<int, int> a, pair<int, int> b) {
            // return (player ? (a.second > b.second) : (a.second < b.second));
            return (a.second < b.second);
        });
    }

    if (playerMoves > 0){
        bestMove = moves[0].first;
    }

    for (auto move : moves) {
        Board newBoard = makeMove(board, move.first, player);
        pair<int, int> result = alphaBetaMax(newBoard, depth - 1, -beta, -alpha, !player);
        result.first = -result.first;
        
        if (result.first > value) {
            value = result.first;
            bestMove = move.first;
        }
        if (value >= beta) {
            break;
        }
        alpha = max(alpha, value);
    }

    return {value, bestMove};
}

int randomMove(Board board, uint64_t moves, bool player){
    vector<int> idxs;
    for(int i = 0; i < 64; i++){
        if(moves & (1ULL << i)){
            idxs.push_back(i);
        }
    }
    
    if (idxs.size() == 0){
        return -1;
    }

    return idxs[rand() % idxs.size()];
}

int bestMove(Board board, bool player, int depth){
    uint64_t moves = getMoves(board, player);
    if (moves == 0) {
        return -1;
    }
    int bestMove = alphaBetaMax(board, depth, INT_MIN, INT_MAX, player).second;

    return bestMove;
}