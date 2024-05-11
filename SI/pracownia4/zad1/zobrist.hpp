#include <random>
#include <vector>
#include <map>
#include "utility.hpp"

typedef unsigned __int128 uint128_t;

using namespace std;

struct Entry {
    uint128_t hash;
    int value;
    short int depth;
    short int type;
};

// class TranspositionTable{
//     private:

//         vector<Entry> table;

//         unsigned int index(uint128_t hash){
//             return hash % table.size();
//         }

//     public:

//         TranspositionTable(int size): table(size) {}

//         TranspositionTable() = default;

//         void reset(){
//             for(auto &entry: table){
//                 entry.value = 0;
//                 entry.depth = 0;
//                 entry.type = 0;
//             }
//         }

//         void put(uint128_t hash, int value, short int depth, short int type){
//             unsigned int idx = index(hash);
//             table[idx].hash = hash;
//             table[idx].value = value;
//             table[idx].depth = depth;
//             table[idx].type = type;
//         }

//         Entry get(uint128_t hash){
//             unsigned int idx = index(hash);
//             if(table[idx].hash == hash){
//                 return table[idx];
//             }
//             return {0, 0, 0, 0};
//         }
// };

class TranspositionTable{
    private:

        map<uint128_t, Entry> table;

    public:

        TranspositionTable() = default;

        void reset(){
            table.clear();
        }

        void put(uint128_t hash, int value, short int depth, short int type){
            table[hash] = {hash, value, depth, type};
        }

        Entry get(uint128_t hash){
            if(table.find(hash) != table.end()){
                cout << "call" << endl;
                return table[hash];
            }
            return {0, 0, 0, 0};
        }
};

uint128_t zHash(Board b) {
    uint128_t bl = b[0];
    uint128_t wt = b[0];
    // return bl;
    return bl | (wt << 64);
}