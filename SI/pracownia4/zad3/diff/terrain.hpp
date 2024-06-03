#if !defined(__terrain__)
#define __terrain__

#include <iostream>

static uint32_t const FLOOR      = 0;
static uint32_t const WATER      = 1;
static uint32_t const WHITE_TRAP = 2;
static uint32_t const BLACK_TRAP = 3;
static uint32_t const WHITE_DEN  = 4;
static uint32_t const BLACK_DEN  = 5;

static uint32_t const CAPTURED = 63;;
static uint32_t const A9 =  0;
static uint32_t const B9 =  1;
static uint32_t const C9 =  2;
static uint32_t const D9 =  3;
static uint32_t const E9 =  4;
static uint32_t const F9 =  5;
static uint32_t const G9 =  6;
static uint32_t const A8 =  7;
static uint32_t const B8 =  8;
static uint32_t const C8 =  9;
static uint32_t const D8 = 10;
static uint32_t const E8 = 11;
static uint32_t const F8 = 12;
static uint32_t const G8 = 13;
static uint32_t const A7 = 14;
static uint32_t const B7 = 15;
static uint32_t const C7 = 16;
static uint32_t const D7 = 17;
static uint32_t const E7 = 18;
static uint32_t const F7 = 19;
static uint32_t const G7 = 20;
static uint32_t const A6 = 21;
static uint32_t const B6 = 22;
static uint32_t const C6 = 23;
static uint32_t const D6 = 24;
static uint32_t const E6 = 25;
static uint32_t const F6 = 26;
static uint32_t const G6 = 27;
static uint32_t const A5 = 28;
static uint32_t const B5 = 29;
static uint32_t const C5 = 30;
static uint32_t const D5 = 31;
static uint32_t const E5 = 32;
static uint32_t const F5 = 33;
static uint32_t const G5 = 34;
static uint32_t const A4 = 35;
static uint32_t const B4 = 36;
static uint32_t const C4 = 37;
static uint32_t const D4 = 38;
static uint32_t const E4 = 39;
static uint32_t const F4 = 40;
static uint32_t const G4 = 41;
static uint32_t const A3 = 42;
static uint32_t const B3 = 43;
static uint32_t const C3 = 44;
static uint32_t const D3 = 45;
static uint32_t const E3 = 46;
static uint32_t const F3 = 47;
static uint32_t const G3 = 48;
static uint32_t const A2 = 49;
static uint32_t const B2 = 50;
static uint32_t const C2 = 51;
static uint32_t const D2 = 52;
static uint32_t const E2 = 53;
static uint32_t const F2 = 54;
static uint32_t const G2 = 55;
static uint32_t const A1 = 56;
static uint32_t const B1 = 57;
static uint32_t const C1 = 58;
static uint32_t const D1 = 59;
static uint32_t const E1 = 60;
static uint32_t const F1 = 61;
static uint32_t const G1 = 62;

static uint32_t const LOCATION_WHITE_DEN = D1;
static uint32_t const LOCATION_BLACK_DEN = D9;

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
};


static inline bool is_white_trap(uint32_t const location)
{
  return TERRAIN[location] == WHITE_TRAP;
}

static inline bool is_black_trap(uint32_t const location)
{
  return TERRAIN[location] == BLACK_TRAP;
}

static inline bool is_not_water(uint32_t const location)
{
  return TERRAIN[location] != WATER;
}

#endif