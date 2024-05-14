// *******************************************************************
//   (C) Copyright 2013 Leiden Institute of Advanced Computer Science
//   Universiteit Leiden
//   All Rights Reserved
// *******************************************************************
// Dou Shou Qi (core)
// *******************************************************************
// FILE INFORMATION:
//   File:     terrain.h
//   Author:   Jonathan K. Vis
//   Revision: 1.01a
//   Date:     2013/04/11
// *******************************************************************
// DESCRIPTION:
//   Defines the terrain layout.
// *******************************************************************

#if !defined(__terrain_h__)
#define __terrain_h__

#include "types.h"

static uint32_t const FLOOR      = 0;
static uint32_t const WATER      = 1;
static uint32_t const WHITE_TRAP = 2;
static uint32_t const BLACK_TRAP = 3;
static uint32_t const WHITE_DEN  = 4;
static uint32_t const BLACK_DEN  = 5;


static uint32_t const TERRAIN[64] =
{
  FLOOR, FLOOR, BLACK_TRAP, BLACK_DEN,  BLACK_TRAP, FLOOR, FLOOR,
  FLOOR, FLOOR, FLOOR,      BLACK_TRAP, FLOOR,      FLOOR, FLOOR,
  FLOOR, FLOOR, FLOOR,      FLOOR,      FLOOR,      FLOOR, FLOOR,
  FLOOR, WATER, WATER,      FLOOR,      WATER,      WATER, FLOOR,
  FLOOR, WATER, WATER,      FLOOR,      WATER,      WATER, FLOOR,
  FLOOR, WATER, WATER,      FLOOR,      WATER,      WATER, FLOOR,
  FLOOR, FLOOR, FLOOR,      FLOOR,      FLOOR,      FLOOR, FLOOR,
  FLOOR, FLOOR, FLOOR,      WHITE_TRAP, FLOOR,      FLOOR, FLOOR,
  FLOOR, FLOOR, WHITE_TRAP, WHITE_DEN,  WHITE_TRAP, FLOOR, FLOOR,
  0xFFFFFFFF
}; // TERRAIN


static inline bool is_white_trap(uint32_t const location)
{
  return TERRAIN[location] == WHITE_TRAP;
} // is_white_trap

static inline bool is_black_trap(uint32_t const location)
{
  return TERRAIN[location] == BLACK_TRAP;
} // is_black_trap

static inline bool is_not_water(uint32_t const location)
{
  return TERRAIN[location] != WATER;
} // is_not_water

#endif
