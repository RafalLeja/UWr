#include "board.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <climits>
#include <queue>

static uint32_t const LOCATION_WEIGHTS[2][64] = {
    {
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 3, 2, 2, 2,
        2, 2, 3, 8, 3, 2, 2,
        2, 3, 8, 10000, 8, 3, 2, 0
    },
    {
        2, 3, 8, 10000, 8, 3, 2,
        2, 2, 3, 8, 3, 2, 2,
        2, 2, 2, 3, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0
    }
};

uint64_t MoveHash(Move m) {
    return ZOBRIST[m.piece][m.to];
}

struct TreeNode {
    int depth;
    Move move;
    int wins;
    int games;
    float score;
    float UCB;
    bool terminal;
    TreeNode* parent;
    vector<TreeNode*> children;
    int allMoves;
    unordered_set<uint64_t> childrenMoves;
    
    TreeNode(Move m, TreeNode* p) : move(m), parent(p) {
        depth = p == nullptr ? 0 : p->depth + 1;
        wins = 0;
        games = 0;
        score = 0;
        UCB = 0;
        allMoves = 0;
        children = vector<TreeNode*>();
        childrenMoves = unordered_set<uint64_t>();
        terminal = false;
    }
    ~TreeNode() {
        for (TreeNode* child : children) {
            delete child;
        }
    }
};

int heuristic(Position& pos) {
    int score = 0;
    int strength_score_w = 0;
    int strength_score_b = 0;
    int piece;

    for (int i = 0; i < 16; i++) {
        piece = pos.piece(i);

        strength_score_b += strength(piece) * (i % 2) * LOCATION_WEIGHTS[0][piece];
        strength_score_w += strength(piece) * !(i % 2) * LOCATION_WEIGHTS[1][piece];
    }

    return strength_score_w - strength_score_b;
}

void bfs(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->depth << " " << node->games << " ucb " <<  node->UCB << " " << node->children.size() << " allMoves " << node->allMoves << endl;
        for (TreeNode* child : node->children) {
            q.push(child);
        }
    }
}

void balance(TreeNode* root) {
    for (TreeNode* child : root->children) {
        cout << child->games << " " << child->score << " " << child->UCB << endl;
    }
}

inline Move randomMove(Position& pos) {
    Move moves[MAX_MOVES];
    int count = pos.generate_moves(moves);
    
    if (count == 0) {
        // cout << "No moves available" << endl;
        return Move();
    }
    return moves[rand() % count];
}

int simulate(Position& pos) {
    while (!pos.is_won() && pos.turn() < 1000) {
        Move m = randomMove(pos);
        pos.do_move(m);
    }
    
    return pos.is_white_turn() ? 0 : 1;
}

TreeNode* selectNode(TreeNode* root) {
    TreeNode* node = root;
    while (node->children.size() == node->allMoves){
        auto bestChild = max_element(node->children.begin(), node->children.end(), [](TreeNode* a, TreeNode* b) {
            return a->UCB < b->UCB;
        });

        if (bestChild == node->children.end()) {
            // cout << "No best child " << node->children.size() << " " << node->allMoves << endl;
            break;
        }

        node = *bestChild;
    }
    return node;
}

int expandNode(TreeNode* node, Position& pos, int itr) {
    Move moves[MAX_MOVES];
    int count = pos.generate_moves(moves);
    random_shuffle(moves, moves + count);
    
    Move m;
    for (int i = 0; i < count; i++) {
        if (node->childrenMoves.find(MoveHash(moves[i])) == node->childrenMoves.end()) {
            m = moves[i];
            break;
        }
    }

    node->childrenMoves.insert(MoveHash(m));
    TreeNode* newNode = new TreeNode(m, node);
    node->children.push_back(newNode);
    node = newNode;
    pos.do_move(m);
    newNode->allMoves = pos.generate_moves(moves);
    newNode->terminal = pos.is_won();
    
    // if (pos.is_won()) {
    //     node->terminal = true;
    //     return pos.is_white_turn() ? 0 : 1;
    // }
    int result = 0;
    for (int i = 0; i < itr; i++) {
        result += simulate(pos);
        // result += heuristic(pos) > 0 ? 1 : 0;
    }

    newNode->wins = result;
    newNode->games = itr;
    newNode->score = (float)result / itr;
    newNode->UCB = (float)node->score + 1.414 * sqrt(log((node->parent->games)+1) / node->games);

    return result;
}

void backpropagate(TreeNode* node, int result, int itr) {
    while (node->parent != nullptr) {
        node->wins += result;
        node->games += itr;
        node->score = (float)node->wins / node->games;
        node->UCB = (float)node->score + 1.414 * sqrt(log(node->parent->games) / node->games);
        node = node->parent;
    }
    node->wins += result;
    node->games += itr;
}

void advance(TreeNode* node, TreeNode* next) {
    for (TreeNode* child : node->children) {
        if (child != next) {
            delete child;
        }
    }

    node->children.clear();
    next->parent = nullptr;
}

TreeNode* advanceMove(TreeNode* node, Position& pos, Move m) {
    TreeNode* next = nullptr;
    for (TreeNode* child : node->children) {
        if (MoveHash(child->move) == MoveHash(m)) {
            next = child;
        } else {
            delete child;
        }
    }

    node->children.clear();
    
    if (next == nullptr) {
        next = new TreeNode(m, node);
        Move moves[MAX_MOVES];
        next->allMoves = pos.generate_moves(moves);
    }

    next->parent = nullptr;
    return next;
}

Move bestMoveMCTS(TreeNode* root, Position& P, int itr) {
    const int SIMS = 1;
    Position pos = Position(P);
    bool color = pos.is_white_turn();

    for (int i = 0; i < itr; i++) {
        TreeNode* next = selectNode(root);
        int result = expandNode(next, pos, SIMS);
        backpropagate(next, result, SIMS);
    }

    TreeNode* res = root->children[0];
    float bestScore = 0;
    for (TreeNode* child : root->children) {
        if (abs(!color - child->score) > bestScore) {
            bestScore = abs(!color - child->score);
            res = child;
        }
    }
    

    // cout << "best Score " << bestScore << " child score " << res->score << endl;

    // advance(root, res);
    // *root = *res;
    return res->move;
}