#include "reversi.hpp"

#include <ctime>
#include <iostream>


int main() {
    srand(time(NULL));

    Board board = {0x0000001008000000, 0x0000000810000000};
    string line;
    bool player = false;
    int ansTime = 0;
    int gameTime = 0;

    cout << "RDY" << endl;
    cin >> line;
    if (line[0] == 'U')
    {
        player = true;
        cout << "IDO 3 2" << endl;
        board = makeMove(board, 19, player);
        cin >> line;
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
            int move = x * 8 + y;
            board = makeMove(board, move, !player);

            cerr << "Time: " << ansTime << " " << gameTime << endl;

            int best = bestMove(board, player, 5);
            cout << "IDO " << best / 8 << " " << best % 8 << endl;
            board = makeMove(board, best, player);
            cin >> line;
        } else {
            board = {0x0000001008000000, 0x0000000810000000};
            player = false;
            cout << "RDY" << endl;
            cin >> line;
            if (line[0] == 'U')
            {
                player = true;
                cout << "IDO 3 2" << endl;
                board = makeMove(board, 19, player);
                cin >> line;
            }
        }        
    }
    
    

}