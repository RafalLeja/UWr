#include "./liacs/location.h"
#include "./liacs/move.h"
#include "./liacs/movement.h"
#include "./liacs/pieces.h"
#include "./liacs/position.h"
#include "./liacs/terrain.h"
#include "./liacs/types.h"
#include "./liacs/zobrist.h"
#include "./liacs/search.h"

using namespace std;
struct command
{
    char cmd;
    int v1;
    int v2;
    int v3;
    int v4;
};


class Player{
    public:
        Position pos;
        bool color;
        int depth;
        Player(int d){
            depth = d;
            this->reset();
        }

        void reset() {
            pos = Position();
            color = true;
            say("RDY");
        }

        void say(string what) {
            cout << what << endl;
        }

        struct command listen() {
            struct command cmd;
            string line;
            getline(cin, line);
            cmd.cmd = line[0];
            if (cmd.cmd != 'U' && cmd.cmd != 'H') return cmd;
            int s = line.find_first_of(' ') + 1;
            int e = line.find_first_of(' ', s);

            cmd.v1 = stoi(line.substr(s, e - s));
            s = e + 1;
            e = line.find_first_of(' ', s);
            cmd.v2 = stoi(line.substr(s, e - s));

            if (cmd.cmd == 'U') return cmd;

            s = e + 1;
            e = line.find_first_of(' ', s);
            cmd.v3 = stoi(line.substr(s, e - s));
            s = e + 1;
            e = line.find_first_of(' ', s);
            cmd.v4 = stoi(line.substr(s, e - s));
            return cmd;
        }

        void loop() {
            while (true) {
                struct command cmd = listen();
                // cerr << "Received command: " << cmd.cmd << " " << cmd.v1 << " " << cmd.v2 << " " << cmd.v3 << " " << cmd.v4 << endl;
                if (cmd.cmd == 'H') {
                    Move move = abs(7 - cmd.v3) + cmd.v4 * 8;
                    board = makeMove(board, move, !color);
                    // cerr << "Move: " << move << " bin " << (1ULL << move) << endl;
                    // cerr << "black " << R.board[0] << endl;
                    // cerr << "white " << R.board[1] << endl;
                } else if (cmd.cmd == 'O')
                {
                    this->reset();
                    continue;
                } else if (cmd.cmd == 'B')
                {
                    break;
                } else if (cmd.cmd == 'U')
                {
                    color = false;
                }

                int best = bestMove(board, color, depth);
                // cerr << "Best move: " << best << " bin " << (1ULL << best) << endl;
                if (best == -1) {
                    this->say("IDO -1 -1");
                    continue;
                }
                board = makeMove(board, best, color);
                string ans = "IDO " + to_string(abs(7 - best % 8)) + " " + to_string(best / 8);
                this->say(ans);
            }
        }


};