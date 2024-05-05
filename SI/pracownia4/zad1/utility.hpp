#include <iostream>
#include <vector>
#include <climits>
#include <utility>
#include <cstdlib>

using namespace std;

typedef vector<vector<char>> Board;

char get(const Board &board, int x, int y);
bool canBeat(const Board &board, int x, int y, int dx, int dy, bool player);
vector<pair<int, int>> getMoves(const Board &board, bool player);

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


