#include "reversi.hpp"

#include <ctime>
#include <iostream>


int main() {
    srand(time(NULL));

    Board board = {0x0000001008000000, 0x0000000810000000};
    string line = "";
    bool player = true;
    int ansTime = 0;
    int gameTime = 0;
    int x = 0;
    int y = 0;
    int best;

    cout << "RDY" << endl;
    getline(cin, line);

    if (line[0] == 'U')
    {
        player = false;
        best = bestMove(board, player, 5);
        board = makeMove(board, best, player);
        // best = abs(64-best);
        // printBoard(board);
        cout << "IDO " << abs(7 - best % 8) << " " << best / 8 << endl;

        getline(cin, line);

    }
    while (line[0] != 'B')
    {
        if (line[0] == 'H') {
            int s = line.find_first_of(' ') + 1;
            int e = line.find_first_of(' ', s);

            ansTime = stoi(line.substr(s, e - s));
            s = e + 1;
            e = line.find_first_of(' ', s);
            gameTime = stoi(line.substr(s, e - s));
            s = e + 1;
            e = line.find_first_of(' ', s);
            int x = stoi(line.substr(s, e - s));
            s = e + 1;
            e = line.find_first_of(' ', s);
            int y = stoi(line.substr(s, e - s));
            int move = abs(7 - x) + y * 8;
            board = makeMove(board, move, !player);
            // printBoard(board);
            cerr << board[0] << "\n" << board[1] << endl;
            // cerr << "Time: " << ansTime << endl;

            best = bestMove(board, player, 5);
            board = makeMove(board, best, player);
            // best = abs(64-best);
            cerr << "Best move: " << best << " bin " << (1ULL << best) << endl;
            cout << "IDO " << abs(7 - best % 8) << " " << best / 8 << endl;
            getline(cin, line);
        } else if (line[0] == 'O') {
            cerr << "RESET" << endl;
            board = {0x0000001008000000, 0x0000000810000000};
            player = true;
            fflush(stdin);
            cout << "RDY" << endl;
            cerr << "READY" << endl;

            getline(cin, line);
            cerr << "LINE: " << line << endl;
            
            

            if (line[0] == 'U')
            {
                player = false;
                best = bestMove(board, player, 5);
                cout << "IDO " << abs(7 - best % 8) << " " << best / 8 << endl;
                board = makeMove(board, best, player);
                getline(cin, line);
            }
        }        
    }
    
    

}