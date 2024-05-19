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
            // P.print();
            // cin.get();
            if (P.is_white_turn() == simColor) {
                m = simSearch(P, 10);
            } else {
                m = bestMove(P, 3);
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