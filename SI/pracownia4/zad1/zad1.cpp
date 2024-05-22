#include "reversi.hpp"
#include <chrono>

#define N 1000

#include <ctime>


int main() {
    srand(time(NULL));
    int random = 0;
    int agent = 0;
    int games = 0;

    bool agentPlayer = true;
    bool randomPlayer = false;

    long long int time = 0;

    while(games < N) {
        Board board = {0x0000001008000000, 0x0000000810000000};
        bool currentPlayer = false;
        Board prevBoard = {0, 0};

        uint64_t playerMoves = getMoves(board, currentPlayer);
        uint64_t oppMoves = getMoves(board, !currentPlayer);

        while(playerMoves > 0 || oppMoves > 0) {
            if(playerMoves > 0) {
                if(currentPlayer == agentPlayer) {
                    auto start = std::chrono::high_resolution_clock::now();
                    int move = bestMove(board, currentPlayer, 5);
                    auto end = std::chrono::high_resolution_clock::now();
                    time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                    board = makeMove(board, move, currentPlayer);
                } else {
                    int move = randomMove(board, playerMoves, currentPlayer);
                    board = makeMove(board, move, currentPlayer);
                }
            }
            if (prevBoard[0] == board[0] && prevBoard[1] == board[1]) {
                board = makeMove(board, randomMove(board, playerMoves, currentPlayer), currentPlayer);
            }
            prevBoard = board;
            
            currentPlayer = !currentPlayer;
            playerMoves = getMoves(board, currentPlayer);
            oppMoves = getMoves(board, !currentPlayer);
        }

        int score = result(board);
        if(score > 0 && agentPlayer) {
            agent++;
        } else if(score > 0 && randomPlayer) {
            random++;
        } else if(score < 0 && agentPlayer) {
            random++;
        } else if(score < 0 && randomPlayer) {
            agent++;
        }
        games++;
        agentPlayer = !agentPlayer;
        randomPlayer = !randomPlayer;
        if (games % 50 == 0) {
            cout << "Game: " << games << " Agent: " << agent << " Random: " << random << endl;
        }
    }
    cout << "Agent: " << agent << " Random: " << random << endl;
    cout << "Time: " << (float) time/1000000 << endl;
}