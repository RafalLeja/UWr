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

#define N 10


int main() {
    srand(time(NULL));
    
    Position P = Position();
    P.initial();
    Move m;
    int randomWins = 0;
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
                m = bestMoveMCTS(P, 100);
            } else {
                m = randomMove(P);
            }
            P.do_move(m);
        }

        if (P.is_white_turn() == simColor) {
            randomWins++;
        } else {
            simWins++;
        }
        games++;

        P.initial();
        simColor = !simColor;

        cout << "sim/rand " << simWins << "/" << randomWins << " games " << games << endl;
    }
    
    return 0;
}