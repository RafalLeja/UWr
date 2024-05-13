#include <iostream>

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