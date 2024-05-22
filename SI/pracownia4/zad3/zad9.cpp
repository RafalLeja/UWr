#include "./liacs/location.h"
#include "./liacs/move.h"
#include "./liacs/movement.h"
#include "./liacs/pieces.h"
#include "./liacs/position.h"
#include "./liacs/terrain.h"
#include "./liacs/types.h"
#include "./liacs/zobrist.h"
#include "./liacs/MCTS.h"

using namespace std;

#define N 20


int main() {
    srand(time(NULL));
    
    Position P = Position();
    P.initial();
    Move m;
    TreeNode* root = new TreeNode(Move(), nullptr);
    Move moves[MAX_MOVES];
    root->allMoves = P.generate_moves(moves);
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
            // cout << "---" << endl;
            if (P.is_white_turn() == simColor) {
                // cout << root->wins << " " << root->games << " " << root->score << " " << root->UCB << endl;
                m = bestMoveMCTS(root, P, 50000);
                // cout << root->wins << " " << root->games << " " << root->score << " " << root->UCB << endl;
            } else {
                m = randomMove(P);
            }
            // bfs(root);
            P.do_move(m);
            root = advanceMove(root, P, m);
        }

        if (P.is_white_turn() == simColor) {
            randomWins++;
        } else {
            simWins++;
        }
        games++;

        P.initial();
        root = new TreeNode(Move(), nullptr);
        Move moves[MAX_MOVES];
        root->allMoves = P.generate_moves(moves);
        simColor = !simColor;

        cout << "sim/rand " << simWins << "/" << randomWins << " games " << games << endl;
    }
    
    return 0;
}