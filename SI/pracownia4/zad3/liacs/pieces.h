// *******************************************************************
//   (C) Copyright 2013 Leiden Institute of Advanced Computer Science
//   Universiteit Leiden
//   All Rights Reserved
// *******************************************************************
// Dou Shou Qi (core)
// *******************************************************************
// FILE INFORMATION:
//   File:     pieces.h
//   Author:   Jonathan K. Vis
//   Revision: 1.01a
//   Date:     2013/04/11
// *******************************************************************
// DESCRIPTION:
//   Defines the pieces and all their capabilities execpt for their
//   movement behavior (see movement.h).
// *******************************************************************

#if !defined(__pieces_h__)
#define __pieces_h__

#include "types.h"

static uint32_t const WHITE = 0;
static uint32_t const BLACK = 1;

// this is a special (non-existing) piece
static uint32_t const NONE = 16;

static uint32_t const WHITE_RAT      =  0;
static uint32_t const BLACK_RAT      =  1;
static uint32_t const WHITE_CAT      =  2;
static uint32_t const BLACK_CAT      =  3;
static uint32_t const WHITE_WOLF     =  4;
static uint32_t const BLACK_WOLF     =  5;
static uint32_t const WHITE_DOG      =  6;
static uint32_t const BLACK_DOG      =  7;
static uint32_t const WHITE_PANTHER  =  8;
static uint32_t const BLACK_PANTHER  =  9;
static uint32_t const WHITE_TIGER    = 10;
static uint32_t const BLACK_TIGER    = 11;
static uint32_t const WHITE_LION     = 12;
static uint32_t const BLACK_LION     = 13;
static uint32_t const WHITE_ELEPHANT = 14;
static uint32_t const BLACK_ELEPHANT = 15;


static inline bool is_white(uint32_t const piece)
{
  return (piece & 1) == WHITE;
} // is_white

static inline bool is_black(uint32_t const piece)
{
  return (piece & 1) == BLACK;
} // is_black

static inline uint32_t strength(uint32_t const piece)
{
  return piece >> 1;
} // strength

static inline bool is_enemy(uint32_t const piece_a,
                            uint32_t const piece_b)
{
  return ((piece_a ^ piece_b) & 1) == 1;
} // is_enemy


// this function is branchless
// checks if piece_a can capture piece_b (piece_b may be NONE)
// no rat captures elephants are checked here
static inline bool can_capture(uint32_t const piece_a,
                               uint32_t const piece_b)
{
  return ((piece_b == NONE) |
          (is_enemy(piece_a, piece_b) &
           (strength(piece_a) >= strength(piece_b)))) == 1;
} // can_capture

#endif
