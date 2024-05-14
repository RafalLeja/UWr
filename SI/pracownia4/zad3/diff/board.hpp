#include "movement.hpp"
#include "animals.hpp"
#include "terrain.hpp"
#include "zobrist.hpp"

class State {
    private:
        uint32_t board[64];
        uint32_t pieces[17];
        int turn;
        uint64_t hash;

        void setPiece(uint32_t location, uint32_t piece);

    public:
        void clear();
        void init();
        bool terminal();
        void makeMove(Move move);
        void unmakeMove(Move move);
        void do_null_move(void);
        void undo_null_move(void);
        bool can_step(uint32_t const piece,
                      uint32_t const direction,
                      uint32_t      &to) const;
        bool can_step_white_rat(uint32_t const direction,
                                uint32_t      &to) const;
        bool can_step_black_rat(uint32_t const direction,
                                uint32_t      &to) const;
        bool can_leap_short(uint32_t const piece,
                            uint32_t const direction,
                            uint32_t      &to) const;                       
        bool can_leap_long(uint32_t const piece,
                            uint32_t const direction,
                            uint32_t      &to) const;                   
        bool is_not_blocked_short(uint32_t const from,
                                  uint32_t const direction) const;
        bool is_not_blocked_long(uint32_t const from,
                                    uint32_t const direction) const;                        
        bool can_move(uint32_t const piece,
                        uint32_t const from,
                        uint32_t const direction,
                        uint32_t      &to) const;                               

};

inline void State::setPiece(uint32_t location, uint32_t piece) {
    board[location] = piece;
    pieces[piece] = location;
    return;
}

inline void State::clear() {
    for (int i = 0; i < 64; i++) {
        board[i] = NONE;
    }
    for (int i = 0; i < 17; i++) {
        pieces[i] = CAPTURED;
    }
    turn = 0;
    hash = 0;
    return;
}

inline void State::init() {
    clear();
    setPiece(G3, WHITE_RAT);
    setPiece(A7, BLACK_RAT);
    setPiece(B2, WHITE_CAT);
    setPiece(F8, BLACK_CAT);
    setPiece(F2, WHITE_DOG);
    setPiece(B8, BLACK_DOG);
    setPiece(C3, WHITE_WOLF);
    setPiece(E7, BLACK_WOLF);
    setPiece(E3, WHITE_PANTHER);
    setPiece(C7, BLACK_PANTHER);
    setPiece(A1, WHITE_TIGER);
    setPiece(G9, BLACK_TIGER);
    setPiece(G1, WHITE_LION);
    setPiece(A9, BLACK_LION);
    setPiece(A3, WHITE_ELEPHANT);
    setPiece(G7, BLACK_ELEPHANT);
    return;
}

bool State::terminal() {
    return board[D9] != NONE | board[D1] != NONE |
        (pieces[WHITE_RAT] == CAPTURED &
        pieces[WHITE_CAT] == CAPTURED &
        pieces[WHITE_DOG] == CAPTURED &
        pieces[WHITE_WOLF] == CAPTURED &
        pieces[WHITE_PANTHER] == CAPTURED &
        pieces[WHITE_TIGER] == CAPTURED &
        pieces[WHITE_LION] == CAPTURED &
        pieces[WHITE_ELEPHANT] == CAPTURED) |
        (pieces[BLACK_RAT] == CAPTURED &
        pieces[BLACK_CAT] == CAPTURED &
        pieces[BLACK_DOG] == CAPTURED &
        pieces[BLACK_WOLF] == CAPTURED &
        pieces[BLACK_PANTHER] == CAPTURED &
        pieces[BLACK_TIGER] == CAPTURED &
        pieces[BLACK_LION] == CAPTURED &
        pieces[BLACK_ELEPHANT] == CAPTURED);
}

inline void State::makeMove(Move move) {
    board[move.from] = NONE;
    board[move.to] = move.piece;
    pieces[move.piece] = move.to;
    pieces[move.enemy] = CAPTURED;
    turn++;
    hash ^= zobristTable[move.piece][move.from] ^ zobristTable[move.piece][move.to] ^ zobristTable[move.enemy][mvoe.to];
    return;
}

inline void State::unmakeMove(Move move) {
    board[move.from] = move.piece;
    board[move.to] = move.enemy;
    pieces[move.piece] = move.from;
    pieces[move.enemy] = move.to;
    turn--;
    hash ^= zobristTable[move.piece][move.from] ^ zobristTable[move.piece][move.to] ^ zobristTable[move.enemy][move.to];
    return;
}

inline void State::do_null_move(void)
{
    ++turn;
    hash ^= zobristTable[NONE][CAPTURED];
    return;
}

inline void State::undo_null_move(void)
{
    --turn;
    hash ^= zobristTable[NONE][CAPTURED];
    return;
}

inline bool State::can_step(uint32_t const piece,
                               uint32_t const direction,
                               uint32_t      &to) const
{
    bool const valid = can_move(piece,
                                pieces[piece],
                                direction,
                                to);
    return (valid & (can_capture(piece, _board[to]) |
                    is_trapped(_board[to], to))) == 1;
} // State::can_step

inline bool State::can_step_white_rat(uint32_t const direction,
                                         uint32_t      &to) const
{
  bool const valid = can_move(WHITE_RAT,
                              _piece[WHITE_RAT],
                              direction,
                              to);
  return (valid & (can_capture(WHITE_RAT, _board[to]) |
                   is_trapped(_board[to], to) |
                   (is_not_water(_piece[WHITE_RAT]) &
                    (_board[to] == BLACK_ELEPHANT)))) == 1;
} // State::can_step_white_rat

inline bool State::can_step_black_rat(uint32_t const direction,
                                         uint32_t      &to) const
{
  bool const valid = can_move(BLACK_RAT,
                              _piece[BLACK_RAT],
                              direction,
                              to);
  return (valid & (can_capture(BLACK_RAT, _board[to]) |
                   is_trapped(_board[to], to) |
                   (is_not_water(_piece[BLACK_RAT]) &
                    (_board[to] == WHITE_ELEPHANT)))) == 1;
} // State::can_step_black_rat

inline bool State::can_leap_short(uint32_t const piece,
                                     uint32_t const direction,
                                     uint32_t      &to) const
{
  bool const valid = can_move(piece,
                              _piece[piece],
                              direction,
                              to);
  return (valid & can_capture(piece, _board[to]) &
          is_not_blocked_short(_piece[piece],
                               direction - LEAP_NORTH)) == 1;
} // State::can_leap_short

inline bool State::can_leap_long(uint32_t const piece,
                                    uint32_t const direction,
                                    uint32_t      &to) const
{
  bool const valid = can_move(piece,
                              _piece[piece],
                              direction,
                              to);
  return (valid & can_capture(piece, _board[to]) &
          is_not_blocked_long(_piece[piece],
                              direction - LEAP_NORTH)) == 1;
} // State::can_leap_long

inline bool State::is_not_blocked_short(uint32_t const from,
                                           uint32_t const direction) const
{
  return ((_board[(from + MOVEMENT_OFFSET[direction]) & 63] == NONE) & 
          (_board[(from + MOVEMENT_OFFSET[direction] * 2) & 63] == NONE)) == 1;
} // State::is_not_blocked_short

inline bool State::is_not_blocked_long(uint32_t const from,
                                          uint32_t const direction) const
{
  return ((_board[(from + MOVEMENT_OFFSET[direction]) & 63] == NONE) &
          (_board[(from + MOVEMENT_OFFSET[direction] * 2) & 63] == NONE) &
          (_board[(from + MOVEMENT_OFFSET[direction] * 3) & 63] == NONE)) == 1;
} // State::is_not_blocked_long
