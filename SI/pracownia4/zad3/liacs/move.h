// *******************************************************************
//   (C) Copyright 2013 Leiden Institute of Advanced Computer Science
//   Universiteit Leiden
//   All Rights Reserved
// *******************************************************************
// Dou Shou Qi (core)
// *******************************************************************
// FILE INFORMATION:
//   File:     move.h
//   Author:   Jonathan K. Vis
//   Revision: 1.01a
//   Date:     2013/04/12
// *******************************************************************
// DESCRIPTION:
//   Defines the move structure.
// *******************************************************************

#if !defined(__move_h__)
#define __move_h__

#include "pieces.h"
#include "types.h"

// as each side has eight pieces which can all move in a maximum of
// four directions the maximum number of possible moves in any given
// configuration is 32
static int const MAX_MOVES = 32;


struct Move
{
  explicit inline Move(void) { }

  explicit inline Move(uint32_t const piece,
                       uint32_t const from,
                       uint32_t const to,
                       uint32_t const enemy):
                  piece(piece), from(from), to(to), enemy(enemy) { }


  bool is_capture(void) const;


  bool operator==(Move const &move) const;


  uint32_t piece;
  uint32_t from;
  uint32_t to;
  uint32_t enemy;

}; //Move


inline bool Move::is_capture(void) const
{
  return enemy != NONE;
} // Move::is_capture

inline bool Move::operator==(Move const &move) const
{
  return ((piece == move.piece) & (to == move.to)) == 1;
} // Move::operator==

#endif
