#include "./diff/animals.hpp"
#include "./diff/board.hpp"
#include "./diff/movement.hpp"
#include "./diff/search.hpp"
#include "./diff/terrain.hpp"
#include "./diff/zobrist.hpp"

using namespace std;

#define N 50


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
                m = simSearch(P, 10);
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