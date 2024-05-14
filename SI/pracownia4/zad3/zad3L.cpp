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

int main() {
    Position P = Position();
    P.initial();

    while (!P.is_won())
    {
        P.print();
        cin.get();
        Move m = simSearch(P,5);
        P.do_move(m);
    }
    
    return 0;
}