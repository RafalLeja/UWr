#include "./diff/animals.hpp"
#include "./diff/board.hpp"
#include "./diff/movement.hpp"
#include "./diff/search.hpp"
#include "./diff/terrain.hpp"
#include "./diff/zobrist.hpp"


using namespace std;

#define N 50

int main() {
    Position P = Position();
    P.initial();
    Move m;
    int abWins = 0;
    int simWins = 0;
    int games = 0;
    bool simColor = true;

    while (games < N)
    {
        while (!P.is_won())
        {
            // cout << "move" << endl;
            // P.print();
            // cin.get();
            if (P.is_white_turn() == simColor) {
                m = simSearch(P, 15);
            } else {
                m = bestMove(P, 5);
            }
            P.do_move(m);
        }

        if (P.is_white_turn() == simColor) {
            abWins++;
        } else {
            simWins++;
        }
        games++;

        P.initial();
        simColor = !simColor;

        cout << "sim/a-b " << simWins << "/" << abWins << " games " << games << endl;
    }
    
    return 0;
}