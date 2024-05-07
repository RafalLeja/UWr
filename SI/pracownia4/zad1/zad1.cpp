#include "reversi.hpp"

#define N 500

int main() {
    int random = 0;
    int agent = 0;
    int games = 0;

    bool agentPlayer = true;
    bool randomPlayer = false;

    while(games < N) {
        Board board = {0x0000001008000000, 0x0000000810000000};
        bool currentPlayer = false;

        uint64_t playerMoves = getMoves(board, currentPlayer);
        uint64_t oppMoves = getMoves(board, !currentPlayer);

        while(playerMoves > 0 || oppMoves > 0) {
            if(playerMoves > 0) {
                if(currentPlayer == agentPlayer) {
                    int move = bestMove(board, currentPlayer, 5);
                    board = makeMove(board, move, currentPlayer);
                    // cout << "Agent move " << move.first << " " << move.second << endl;
                } else {
                    int move = randomMove(board, playerMoves, currentPlayer);
                    board = makeMove(board, move, currentPlayer);
                    // cout << "Random move " << move.first << " " << move.second << endl;
                }
            }

            // heuristic2(board, playerMoves, oppMoves);
            // printBoard(board);
            // cin.get();
            
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
        if (games % 10 == 0) {
            cout << "Game: " << games << " Agent: " << agent << " Random: " << random << endl;
        }
    }
    cout << "Agent: " << agent << " Random: " << random << endl;
}