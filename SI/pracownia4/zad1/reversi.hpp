#include "heuristics.hpp"
#include <algorithm>

#define SORTING true

Board initBoard();
void printBoard(const Board &board);
Board makeMove(Board &board, pair<int, int> move, bool player);
int result(const Board &board);
int heuristic(const Board &board);
bool terminal(const Board &board);
int alphaBeta(const Board &board, int depth, int alpha, int beta, bool player);
pair<int, int> randomMove(const Board &board, bool player);
pair<int, int> bestMove(const Board &board, bool player, int depth);


Board initBoard(){
    Board board(8, vector<char>(8, '.'));
    board[3][3] = board[4][4] = 'O';
    board[3][4] = board[4][3] = '#';
    return board;
}

void printBoard(const Board &board){
    cout << "  0 1 2 3 4 5 6 7" << endl;
    for(int i = 0; i < 8; i++){
        cout << i << " ";
        for(int j = 0; j < 8; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

Board makeMove(Board &board, pair<int, int> move, bool player){
    int x = move.first;
    int y = move.second;
    board[x][y] = player ? '#' : 'O';
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            if(dx == 0 && dy == 0){
                continue;
            }
            if(canBeat(board, x, y, dx, dy, player)){
                int i = x + dx;
                int j = y + dy;
                while(board[i][j] == (!player ? '#' : 'O')){
                    board[i][j] = player ? '#' : 'O';
                    i += dx;
                    j += dy;
                }
            }
        }
    }
    return board;
}

int result(const Board &board){
    int score = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == '#'){
                score++;
            }
            if(board[i][j] == 'O'){
                score--;
            }
        }
    }
    return score;
}

int heuristic(const Board &board){
    int weights[ 8 ][ 8 ] = {
         {200, -100, 100,  50,  50, 100, -100,  200},
        {-100, -200, -50, -50, -50, -50, -200, -100},
         {100,  -50, 100,   0,   0, 100,  -50,  100},
          {50,  -50,   0,   0,   0,   0,  -50,   50},
          {50,  -50,   0,   0,   0,   0,  -50,   50},
         {100,  -50, 100,   0,   0, 100,  -50,  100},
        {-100, -200, -50, -50, -50, -50, -200, -100},
         {200, -100, 100,  50,  50, 100, -100,  200}
    };
    int weighted_score = 0;
    int result = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == '#'){
                weighted_score += weights[i][j];
                result++;
            }
            if(board[i][j] == 'O'){
                weighted_score -= weights[i][j];
                result--;
            }
        }
    }
    // cout << "Weighted score: " << weighted_score << " Result: " << result << " Corners: " << corners(board, true) << " Mobility: " << mobility(board, true) << endl;
    int score = 0;
    score += weighted_score;
    score += result * 100;
    // score += stability(board, true) * 25;
    score += corners(board, true) * 300;
    // score += mobility(board, true) * 5;

    return score;
}

bool terminal(const Board &board){
    return getMoves(board, true).empty() && getMoves(board, false).empty();
}

int alphaBeta(const Board &board, int depth, int alpha, int beta, bool player){
    if(depth == 0 || terminal(board)){
        return heuristic(board);
    }
    if(player){
        int value = INT_MIN;
        vector<pair<int, int>> moves = getMoves(board, player);
        if (SORTING) {
            sort(moves.begin(), moves.end(), [&](pair<int, int> a, pair<int, int> b) {
                Board newBoardA = board;
                newBoardA  = makeMove(newBoardA, a, player);
                Board newBoardB = board;
                newBoardB = makeMove(newBoardB, b, player);
                return heuristic(newBoardA) > heuristic(newBoardB);
            });
        }

        for (auto move : moves) {
            Board newBoard = board;
            newBoard = makeMove(newBoard, move, player);
            value = max(value, alphaBeta(newBoard, depth - 1, alpha, beta, !player));
            alpha = max(alpha, value);
            if (alpha >= beta) {
                break;
            }
        }
        return value;
    } else {
        int value = INT_MAX;
        vector<pair<int, int>> moves = getMoves(board, player);
        if (SORTING) {
            sort(moves.begin(), moves.end(), [&](pair<int, int> a, pair<int, int> b) {
                Board newBoardA = board;
                newBoardA  = makeMove(newBoardA, a, player);
                Board newBoardB = board;
                newBoardB = makeMove(newBoardB, b, player);
                return heuristic(newBoardA) < heuristic(newBoardB);
            });
        }

        for(auto move : moves){
            Board newBoard = board;
            newBoard = makeMove(newBoard, move, player);
            makeMove(newBoard, move, player);
            value = min(value, alphaBeta(newBoard, depth - 1, alpha, beta, !player));
            beta = min(beta, value);
            if(alpha >= beta){
                break;
            }
        }
        return value;
    }
}

pair<int, int> randomMove(const Board &board, bool player){
    vector<pair<int, int>> moves = getMoves(board, player);
    return moves[rand() % moves.size()];
}

pair<int, int> bestMove(const Board &board, bool player, int depth){
    vector<pair<int, int>> moves = getMoves(board, player);
    int bestValue = INT_MIN;
    pair<int, int> bestMove = moves[0];
    for(auto move : moves){
        Board newBoard = board;
        newBoard = makeMove(newBoard, move, player);

        int value = alphaBeta(newBoard, depth, INT_MIN, INT_MAX, !player);
        
        if (player){
            if (value > bestValue){
                bestValue = value;
                bestMove = move;
            }
        } else {
            if (value < bestValue){
                bestValue = value;
                bestMove = move;
            }
        }
    }
    return bestMove;
}