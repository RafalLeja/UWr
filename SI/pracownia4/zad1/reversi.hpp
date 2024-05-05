#include <iostream>
#include <vector>
#include <climits>
#include <utility>
#include <cstdlib>


using namespace std;

typedef vector<vector<char>> Board;

Board initBoard();
void printBoard(const Board &board);
char get(const Board &board, int x, int y);
bool canBeat(const Board &board, int x, int y, int dx, int dy, bool player);
vector<pair<int, int>> getMoves(const Board &board, bool player);
Board makeMove(Board &board, pair<int, int> move, bool player);
int result(const Board &board);
int cornesrs(const Board &board);
int mobility(const Board &board);
int stability(const Board &board);
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

char get(const Board &board, int x, int y){
    if(x < 0 || x >= 8 || y < 0 || y >= 8){
        return '.';
    }
    return board[x][y];
}

bool canBeat(const Board &board, int x, int y, int dx, int dy, bool player){
    x += dx;
    y += dy;
    int count = 0;
    while(get(board, x, y) == ((!player) ? '#' : 'O')){
        count++;
        x += dx;
        y += dy;
    }
    return count > 0 && get(board, x, y) == (player ? '#' : 'O');
}

vector<pair<int, int>> getMoves(const Board &board, bool player){
    vector<pair<int, int>> moves;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == '.'){
                bool can = false;
                for(int dx = -1; dx <= 1; dx++){
                    for(int dy = -1; dy <= 1; dy++){
                        if(dx == 0 && dy == 0){
                            continue;
                        }
                        if(canBeat(board, i, j, dx, dy, player)){
                            can = true;
                        }
                    }
                }
                if(can){
                    moves.push_back({i, j});
                }
            }
        }
    }
    return moves;
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

int corners(const Board &board){
    int score = 0;
    if(board[0][0] == '#'){
        score++;
    }
    if(board[0][7] == '#'){
        score++;
    }
    if(board[7][0] == '#'){
        score++;
    }
    if(board[7][7] == '#'){
        score++;
    }
    return score;
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
    int weights[8][8] = {
    { 4, -3,  2,   2,   2,  2, -3, 4},
    {-3, -4,  -1,  -1,  -1,  -1, -4, -3},
    {  2,  -1,   1,   0,   0,   1,  -1,  2},
    {   2,  -1,   0,   1,   1,   0,  -1,   2},
    {   2,  -1,   0,   1,   1,   0,  -1,   2},
    {  2,  -1,   1,   0,   0,   1,  -1,  2},
    {-3, -4,  -1,  -1,  -1,  -1, -4, -3},
    { 4, -3,  2,   2,   2,  2, -3, 4}};

    int score = 0;
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == '#'){
                score += weights[i][j];
            }
            if (board[i][j] == 'O'){
                score -= weights[i][j];
            }
        }
    }
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
        for(auto move : getMoves(board, player)){
            Board newBoard = board;
            newBoard = makeMove(newBoard, move, player);
            value = max(value, alphaBeta(newBoard, depth - 1, alpha, beta, !player));
            alpha = max(alpha, value);
            if(alpha >= beta){
                break;
            }
        }
        return value;
    } else {
        int value = INT_MAX;
        for(auto move : getMoves(board, player)){
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