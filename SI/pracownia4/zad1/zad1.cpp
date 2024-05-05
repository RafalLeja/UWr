#include "reversi.hpp"

#define N 100

int main() {
    int random = 0;
    int agent = 0;
    int games = 0;

    bool agentPlayer = true;
    bool randomPlayer = false;

    while(games < N) {
        Board board = initBoard();
        bool currentPlayer = false;

        while(terminal(board) == false) {
            vector<pair<int, int>> moves = getMoves(board, currentPlayer);
            if(moves.size() > 0) {
                if(currentPlayer == agentPlayer) {
                    pair<int, int> move = bestMove(board, currentPlayer, 3);
                    board = makeMove(board, move, currentPlayer);
                    // cout << "Agent move " << move.first << " " << move.second << endl;
                } else {
                    pair<int, int> move = randomMove(board, currentPlayer);
                    board = makeMove(board, move, currentPlayer);
                    // cout << "Random move " << move.first << " " << move.second << endl;
                }
            }
            // printBoard(board);
            currentPlayer = !currentPlayer;
        }

        int score = result(board);
        if(score > 0) {
            agent++;
        } else if(score < 0) {
            random++;
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