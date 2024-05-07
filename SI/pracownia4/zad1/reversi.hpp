#include "utility.hpp"
#include <algorithm>

#define SORTING true

// Board initBoard();
void printBoard(Board board);
int result(Board board);
int stability(Board board);
int heuristic(Board board, uint64_t playerMoves, uint64_t oppMoves);
pair<int, int> alphaBetaMax(Board board, int depth, int alpha, int beta, bool player);
pair<int, int> alphaBetaMin(Board board, int depth, int alpha, int beta, bool player);
int randomMove(Board board, uint64_t moves, bool player);
int bestMove(Board board, bool player, int depth);

void printBoard(Board board){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[0] & (1ULL << (i * 8 + j))){
                cout << "#";
            } else if(board[1] & (1ULL << (i * 8 + j))){
                cout << "O";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}

int result(Board board){
    return __popcount(board[1]) - __popcount(board[0]);
}

int stability(Board board){
    uint64_t empty = ~(board[1] | board[0]);
    uint64_t playerBorder = 0;
    uint64_t oppBorder = 0;
    uint64_t tmp;
    for(int i = 0; i < 4; i++){
        tmp = (empty >> RSHIFTS[i]);
        playerBorder |= tmp & board[1];
        oppBorder |= tmp & board[0];
    }
    for(int i = 4; i < 8; i++){
        tmp = (empty << LSHIFTS[i]);
        playerBorder |= tmp & board[1];
        oppBorder |= tmp & board[0];
    }

    return __popcount(playerBorder) - __popcount(oppBorder);
}

int heuristic(Board board, uint64_t playerMoves, uint64_t oppMoves){
    int balance = __popcount(board[1]) - __popcount(board[0]);
    if (playerMoves == 0 && oppMoves == 0){
        return balance << 10;
    }
    int mobility = __popcount(playerMoves) - __popcount(oppMoves);
    int corners = (__popcount(board[1] & 0x8100000000000081ULL) - __popcount(board[0] & 0x8100000000000081ULL));
    int nearCorners = (__popcount(board[1] & 0x4200000000000042ULL) - __popcount(board[0] & 0x4200000000000042ULL));
    nearCorners += (__popcount(board[1] & 0x0081000000008100ULL) - __popcount(board[0] & 0x0081000000008100ULL));
    nearCorners += (__popcount(board[1] & 0x0042000000004200ULL) - __popcount(board[0] & 0x0042000000004200ULL));
    
    int score = balance; 
    score += mobility << 2;
    score += corners << 2;
    score -= nearCorners << 6;
    score += stability(board) << 0;
    // cout << "Balance: " << balance << " Mobility: " << mobility << " Corners: " << corners << " NearCorners: " << nearCorners << " Stability: " << stability(board) << endl;
    return score;
}

int heuristic2(Board board, uint64_t playerMoves, uint64_t oppMoves){
    int balance = __popcount(board[1]) - __popcount(board[0]);
    if (playerMoves == 0 && oppMoves == 0){
        return balance << 10;
    }
    int mobility = __popcount(playerMoves) - __popcount(oppMoves);
    int corners = (__popcount(board[1] & 0x8100000000000081ULL) - __popcount(board[0] & 0x8100000000000081ULL));
    int nearCorners = (__popcount(board[1] & 0x4200000000000042ULL) - __popcount(board[0] & 0x4200000000000042ULL));
    nearCorners += (__popcount(board[1] & 0x0081000000008100ULL) - __popcount(board[0] & 0x0081000000008100ULL));
    nearCorners += (__popcount(board[1] & 0x0042000000004200ULL) - __popcount(board[0] & 0x0042000000004200ULL));
    
    int score = balance; 
    score += mobility << 2;
    score += corners << 5;
    score -= nearCorners << 4;
    // score += stability(board);
    cout << "Balance: " << balance << " Mobility: " << mobility << " Corners: " << corners << " NearCorners: " << nearCorners << " Stability: " << stability(board) << endl;
    return score;
}

pair<int, int> alphaBetaMax(Board board, int depth, int alpha, int beta, bool player){
    int value = INT_MIN;
    int bestMove = 1;
    uint64_t playerMoves = getMoves(board, player);
    uint64_t oppMoves = getMoves(board, !player);
    if (depth == 0 || (playerMoves == 0 && oppMoves == 0)){
        return {heuristic(board, playerMoves, oppMoves), -1};
    }

    vector<pair<int, int>> moves;
    for(int i = 0; i < 64; i++){
        if(playerMoves & (1ULL << i)){
            auto tmpBoard = makeMove(board, i, player);
            moves.push_back({i, heuristic(tmpBoard, playerMoves, oppMoves)});
        }
    }

    if (SORTING) {
        sort(moves.begin(), moves.end(), [&](pair<int, int> a, pair<int, int> b) {
            return a.second > b.second;
        });
    }

    for (auto move : moves) {
        Board newBoard = makeMove(board, move.first, player);
        pair<int, int> result = alphaBetaMin(newBoard, depth - 1, alpha, beta, !player);
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

pair<int, int> alphaBetaMin(Board board, int depth, int alpha, int beta, bool player){
    int value = INT_MAX;
    int bestMove = 1;
    uint64_t playerMoves = getMoves(board, player);
    uint64_t oppMoves = getMoves(board, !player);
    if (depth == 0 || (playerMoves == 0 && oppMoves == 0)){
        return {heuristic(board, playerMoves, oppMoves), -1};
    }

    vector<pair<int, int>> moves;
    for(int i = 0; i < 64; i++){
        if(playerMoves & (1ULL << i)){
            auto tmpBoard = makeMove(board, i, player);
            moves.push_back({i, heuristic(tmpBoard, playerMoves, oppMoves)});
        }
    }    

    if (SORTING) {
        sort(moves.begin(), moves.end(), [&](pair<int, int> a, pair<int, int> b) {
            return a.second < b.second;
        });
    }

    for(auto move : moves){
        Board newBoard = makeMove(board, move.first, player);
        pair<int, int> result = alphaBetaMax(newBoard, depth - 1, alpha, beta, !player);
        if(result.first < value){
            value = result.first;
            bestMove = move.first;
        }
        if(value <= alpha){
            break;
        }
        beta = min(beta, value);
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

    return idxs[rand() % idxs.size()];
}

int bestMove(Board board, bool player, int depth){
    int bestMove = alphaBetaMax(board, depth, INT_MIN, INT_MAX, player).second;

    return bestMove;
}