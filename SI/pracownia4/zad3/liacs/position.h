// *******************************************************************
//   (C) Copyright 2013 Leiden Institute of Advanced Computer Science
//   Universiteit Leiden
//   All Rights Reserved
// *******************************************************************
// Dou Shou Qi (core)
// *******************************************************************
// FILE INFORMATION:
//   File:     position.h (implemented in position.cc)
//   Author:   Jonathan K. Vis
//   Revision: 1.01a
//   Date:     2013/04/18
// *******************************************************************
// DESCRIPTION:
//   Defines the position object which contains a (legal) game
//   configuration.
// *******************************************************************

#if !defined(__position_h__)
#define __position_h__

#include "location.h"
#include "move.h"
#include "movement.h"
#include "pieces.h"
#include "terrain.h"
#include "types.h"
#include "zobrist.h"
#include <iostream>

using namespace std;

char const PIECE_NAME[17] = { 'R', 'r', 'C', 'c', 'W', 'w', 'D', 'd',
                              'P', 'p', 'T', 't', 'L', 'l', 'E', 'e', '.' };

static inline bool is_trapped(uint32_t const piece,
                              uint32_t const location)
{
  return ((is_white(piece) & is_black_trap(location)) |
          (is_black(piece) & is_white_trap(location))) == 1;
} // is_trapped

class Position
{
  public:
    explicit Position(void) { }
    Position(Position const &position){
      for (int i = 0; i < 64; ++i)
      {
        _board[i] = position._board[i];
      } // for
      for (int i = 0; i < 17; ++i)
      {
        _piece[i] = position._piece[i];
      } // for
      _turn = position._turn;
      _key = position._key;
    }

    void print();

    void clear(void);
    void initial(void);
    void set_key(uint64_t const key);
    void set_piece(uint32_t const piece,
                   uint32_t const location);


    uint32_t board(uint32_t const location) const;
    uint32_t piece(uint32_t const piece) const;
    int turn(void) const;
    uint64_t key(void) const;


    bool is_captured(uint32_t const piece) const;
    bool is_white_turn(void) const;
    bool is_won(void) const;


    int generate_moves(Move moves[MAX_MOVES]) const;
    void do_move(Move const &move);
    void undo_move(Move const &move);
    void do_null_move(void);
    void undo_null_move(void);


  private:

    int generate_white_moves(Move moves[MAX_MOVES]) const;
    int generate_black_moves(Move moves[MAX_MOVES]) const;

    // these functions are only used to generate legal moves and are
    // branchless
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


    uint32_t _board[64];
    uint32_t _piece[17];
    int      _turn;
    uint64_t _key;

}; // Position


inline void Position::print()
{
  for (int i = 0; i < 64; ++i)
  {
    cout << " " << PIECE_NAME[_board[i]];
    
    if ((i + 1) % 7 == 0)
    {
      cout << endl;
    }
  } // for
  cout << endl;
  return;
} // Position::print

inline void Position::clear(void)
{
  for (int i = 0; i < 64; ++i)
  {
    _board[i] = NONE;
  } // for
  _piece[WHITE_RAT] = CAPTURED;
  _piece[BLACK_RAT] = CAPTURED;
  _piece[WHITE_CAT] = CAPTURED;
  _piece[BLACK_CAT] = CAPTURED;
  _piece[WHITE_WOLF] = CAPTURED;
  _piece[BLACK_WOLF] = CAPTURED;
  _piece[WHITE_DOG] = CAPTURED;
  _piece[BLACK_DOG] = CAPTURED;
  _piece[WHITE_PANTHER] = CAPTURED;
  _piece[BLACK_PANTHER] = CAPTURED;
  _piece[WHITE_TIGER] = CAPTURED;
  _piece[BLACK_TIGER] = CAPTURED;
  _piece[WHITE_LION] = CAPTURED;
  _piece[BLACK_LION] = CAPTURED;
  _piece[WHITE_ELEPHANT] = CAPTURED;
  _piece[BLACK_ELEPHANT] = CAPTURED;
  _piece[NONE] = CAPTURED;
  _turn = 0;
  _key = 0ull;
  return;
} // Position::clear

inline void Position::initial(void)
{
  clear();
  set_piece(WHITE_RAT, G3);
  set_piece(BLACK_RAT, A7);
  set_piece(WHITE_CAT, B2);
  set_piece(BLACK_CAT, F8);
  set_piece(WHITE_WOLF, C3);
  set_piece(BLACK_WOLF, E7);
  set_piece(WHITE_DOG, F2);
  set_piece(BLACK_DOG, B8);
  set_piece(WHITE_PANTHER, E3);
  set_piece(BLACK_PANTHER, C7);
  set_piece(WHITE_TIGER, A1);
  set_piece(BLACK_TIGER, G9);
  set_piece(WHITE_LION, G1);
  set_piece(BLACK_LION, A9);
  set_piece(WHITE_ELEPHANT, A3);
  set_piece(BLACK_ELEPHANT, G7);
  return;
} // Position::initial

inline void Position::set_key(uint64_t const key)
{
  _key = key;
  return;
} // Position::key

inline void Position::set_piece(uint32_t const piece,
                                uint32_t const location)
{
  _board[location] = piece;
  _piece[piece] = location;
  return;
} // Position::set_piece

inline uint32_t Position::board(uint32_t const location) const
{
  return _board[location];
} // Position::board

inline uint32_t Position::piece(uint32_t const piece) const
{
  return _piece[piece];
} // Position::piece

inline int Position::turn(void) const
{
  return _turn;
} // Position::turn

inline uint64_t Position::key(void) const
{
  return _key;
} // Position::key

inline bool Position::is_captured(uint32_t const piece) const
{
  return _piece[piece] == CAPTURED;
} // Position::is_captured

inline bool Position::is_white_turn(void) const
{
  return (static_cast<uint32_t>(_turn) & 1) == WHITE;
} // Position::is_white_turn

inline bool Position::is_won(void) const
{
  return _board[D9] != NONE || _board[D1] != NONE ||
         (is_captured(WHITE_RAT) &
          is_captured(WHITE_CAT) &
          is_captured(WHITE_WOLF) &
          is_captured(WHITE_DOG) &
          is_captured(WHITE_PANTHER) &
          is_captured(WHITE_TIGER) &
          is_captured(WHITE_LION) &
          is_captured(WHITE_ELEPHANT)) == 1 ||
         (is_captured(BLACK_RAT) &
          is_captured(BLACK_CAT) &
          is_captured(BLACK_WOLF) &
          is_captured(BLACK_DOG) &
          is_captured(BLACK_PANTHER) &
          is_captured(BLACK_TIGER) &
          is_captured(BLACK_LION) &
          is_captured(BLACK_ELEPHANT)) == 1;
} // Position::is_won

inline int Position::generate_moves(Move moves[MAX_MOVES]) const
{
  return is_white_turn() ? generate_white_moves(moves) :
                           generate_black_moves(moves);
} // Position::generate_moves

inline void Position::do_move(Move const &move)
{
  _board[move.from] = NONE;
  _board[move.to] = move.piece;
  _piece[move.piece] = move.to;
  _piece[move.enemy] = CAPTURED;
  ++_turn;
  _key ^= ZOBRIST[move.piece][move.from] ^
          ZOBRIST[move.piece][move.to] ^
          ZOBRIST[move.enemy][move.to];
  return;
} // Position::do_move

inline void Position::undo_move(Move const &move)
{
  _board[move.from] = move.piece;
  _board[move.to] = move.enemy;
  _piece[move.piece] = move.from;
  _piece[move.enemy] = move.to;
  --_turn;
  _key ^= ZOBRIST[move.piece][move.from] ^
          ZOBRIST[move.piece][move.to] ^
          ZOBRIST[move.enemy][move.to];
  return;
} // Position::undo_move

inline void Position::do_null_move(void)
{
  ++_turn;
  _key ^= ZOBRIST[NONE][CAPTURED];
  return;
} // Position::do_null_move

inline void Position::undo_null_move(void)
{
  --_turn;
  _key ^= ZOBRIST[NONE][CAPTURED];
  return;
} // Position::undo_null_move

inline bool Position::can_step(uint32_t const piece,
                               uint32_t const direction,
                               uint32_t      &to) const
{
  bool const valid = can_move(piece,
                              _piece[piece],
                              direction,
                              to);
  return (valid & (can_capture(piece, _board[to]) |
                   is_trapped(_board[to], to))) == 1;
} // Position::can_step

inline bool Position::can_step_white_rat(uint32_t const direction,
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
} // Position::can_step_white_rat

inline bool Position::can_step_black_rat(uint32_t const direction,
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
} // Position::can_step_black_rat

inline bool Position::can_leap_short(uint32_t const piece,
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
} // Position::can_leap_short

inline bool Position::can_leap_long(uint32_t const piece,
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
} // Position::can_leap_long

inline bool Position::is_not_blocked_short(uint32_t const from,
                                           uint32_t const direction) const
{
  return ((_board[(from + MOVEMENT_OFFSET[direction]) & 63] == NONE) & 
          (_board[(from + MOVEMENT_OFFSET[direction] * 2) & 63] == NONE)) == 1;
} // Position::is_not_blocked_short

inline bool Position::is_not_blocked_long(uint32_t const from,
                                          uint32_t const direction) const
{
  return ((_board[(from + MOVEMENT_OFFSET[direction]) & 63] == NONE) &
          (_board[(from + MOVEMENT_OFFSET[direction] * 2) & 63] == NONE) &
          (_board[(from + MOVEMENT_OFFSET[direction] * 3) & 63] == NONE)) == 1;
} // Position::is_not_blocked_long

#endif
