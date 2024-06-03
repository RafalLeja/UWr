#if !defined(__moveGen__)
#define __moveGen__

#include "board.hpp"
#include "movement.hpp"

int Position::generate_white_moves(Move moves[MAX_MOVES]) const
{
  int count = 0;
  uint32_t to;
  {
    int const valid = can_step(WHITE_LION, STEP_NORTH, to);
    moves[count] = Move(WHITE_LION,
                        _piece[WHITE_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step_white_rat(STEP_NORTH, to);
    moves[count] = Move(WHITE_RAT,
                        _piece[WHITE_RAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_TIGER, STEP_NORTH, to);
    moves[count] = Move(WHITE_TIGER,
                        _piece[WHITE_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_ELEPHANT, STEP_EAST, to);
    moves[count] = Move(WHITE_ELEPHANT,
                        _piece[WHITE_ELEPHANT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step_white_rat(STEP_WEST, to);
    moves[count] = Move(WHITE_RAT,
                        _piece[WHITE_RAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_LION, STEP_WEST, to);
    moves[count] = Move(WHITE_LION,
                        _piece[WHITE_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_TIGER, STEP_EAST, to);
    moves[count] = Move(WHITE_TIGER,
                        _piece[WHITE_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_ELEPHANT, STEP_NORTH, to);
    moves[count] = Move(WHITE_ELEPHANT,
                        _piece[WHITE_ELEPHANT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_WOLF, STEP_SOUTH, to);
    moves[count] = Move(WHITE_WOLF,
                        _piece[WHITE_WOLF],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_short(WHITE_LION, LEAP_WEST, to);
    moves[count] = Move(WHITE_LION,
                        _piece[WHITE_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_ELEPHANT, STEP_SOUTH, to);
    moves[count] = Move(WHITE_ELEPHANT,
                        _piece[WHITE_ELEPHANT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_ELEPHANT, STEP_WEST, to);
    moves[count] = Move(WHITE_ELEPHANT,
                        _piece[WHITE_ELEPHANT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_LION, STEP_SOUTH, to);
    moves[count] = Move(WHITE_LION,
                        _piece[WHITE_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_CAT, STEP_NORTH, to);
    moves[count] = Move(WHITE_CAT,
                        _piece[WHITE_CAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_WOLF, STEP_EAST, to);
    moves[count] = Move(WHITE_WOLF,
                        _piece[WHITE_WOLF],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_PANTHER, STEP_WEST, to);
    moves[count] = Move(WHITE_PANTHER,
                        _piece[WHITE_PANTHER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_LION, STEP_EAST, to);
    moves[count] = Move(WHITE_LION,
                        _piece[WHITE_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_PANTHER, STEP_NORTH, to);
    moves[count] = Move(WHITE_PANTHER,
                        _piece[WHITE_PANTHER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_PANTHER, STEP_SOUTH, to);
    moves[count] = Move(WHITE_PANTHER,
                        _piece[WHITE_PANTHER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step_white_rat(STEP_SOUTH, to);
    moves[count] = Move(WHITE_RAT,
                        _piece[WHITE_RAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_TIGER, STEP_SOUTH, to);
    moves[count] = Move(WHITE_TIGER,
                        _piece[WHITE_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_CAT, STEP_WEST, to);
    moves[count] = Move(WHITE_CAT,
                        _piece[WHITE_CAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_DOG, STEP_WEST, to);
    moves[count] = Move(WHITE_DOG,
                        _piece[WHITE_DOG],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_TIGER, STEP_WEST, to);
    moves[count] = Move(WHITE_TIGER,
                        _piece[WHITE_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_CAT, STEP_EAST, to);
    moves[count] = Move(WHITE_CAT,
                        _piece[WHITE_CAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_WOLF, STEP_NORTH, to);
    moves[count] = Move(WHITE_WOLF,
                        _piece[WHITE_WOLF],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step_white_rat(STEP_EAST, to);
    moves[count] = Move(WHITE_RAT,
                        _piece[WHITE_RAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_DOG, STEP_NORTH, to);
    moves[count] = Move(WHITE_DOG,
                        _piece[WHITE_DOG],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_CAT, STEP_SOUTH, to);
    moves[count] = Move(WHITE_CAT,
                        _piece[WHITE_CAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_DOG, STEP_SOUTH, to);
    moves[count] = Move(WHITE_DOG,
                        _piece[WHITE_DOG],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_short(WHITE_LION, LEAP_EAST, to);
    moves[count] = Move(WHITE_LION,
                        _piece[WHITE_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_PANTHER, STEP_EAST, to);
    moves[count] = Move(WHITE_PANTHER,
                        _piece[WHITE_PANTHER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_short(WHITE_TIGER, LEAP_EAST, to);
    moves[count] = Move(WHITE_TIGER,
                        _piece[WHITE_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_long(WHITE_LION, LEAP_NORTH, to);
    moves[count] = Move(WHITE_LION,
                        _piece[WHITE_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_long(WHITE_TIGER, LEAP_NORTH, to);
    moves[count] = Move(WHITE_TIGER,
                        _piece[WHITE_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_WOLF, STEP_WEST, to);
    moves[count] = Move(WHITE_WOLF,
                        _piece[WHITE_WOLF],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(WHITE_DOG, STEP_EAST, to);
    moves[count] = Move(WHITE_DOG,
                        _piece[WHITE_DOG],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_short(WHITE_TIGER, LEAP_WEST, to);
    moves[count] = Move(WHITE_TIGER,
                        _piece[WHITE_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_long(WHITE_LION, LEAP_SOUTH, to);
    moves[count] = Move(WHITE_LION,
                        _piece[WHITE_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_long(WHITE_TIGER, LEAP_SOUTH, to);
    moves[count] = Move(WHITE_TIGER,
                        _piece[WHITE_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  return count;
}

int Position::generate_black_moves(Move moves[MAX_MOVES]) const
{
  int count = 0;
  uint32_t to;
  {
    int const valid = can_step(BLACK_LION, STEP_SOUTH, to);
    moves[count] = Move(BLACK_LION,
                        _piece[BLACK_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_TIGER, STEP_SOUTH, to);
    moves[count] = Move(BLACK_TIGER,
                        _piece[BLACK_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step_black_rat(STEP_SOUTH, to);
    moves[count] = Move(BLACK_RAT,
                        _piece[BLACK_RAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_ELEPHANT, STEP_WEST, to);
    moves[count] = Move(BLACK_ELEPHANT,
                        _piece[BLACK_ELEPHANT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step_black_rat(STEP_EAST, to);
    moves[count] = Move(BLACK_RAT,
                        _piece[BLACK_RAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_LION, STEP_EAST, to);
    moves[count] = Move(BLACK_LION,
                        _piece[BLACK_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_TIGER, STEP_WEST, to);
    moves[count] = Move(BLACK_TIGER,
                        _piece[BLACK_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_ELEPHANT, STEP_SOUTH, to);
    moves[count] = Move(BLACK_ELEPHANT,
                        _piece[BLACK_ELEPHANT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_WOLF, STEP_NORTH, to);
    moves[count] = Move(BLACK_WOLF,
                        _piece[BLACK_WOLF],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_ELEPHANT, STEP_NORTH, to);
    moves[count] = Move(BLACK_ELEPHANT,
                        _piece[BLACK_ELEPHANT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_ELEPHANT, STEP_EAST, to);
    moves[count] = Move(BLACK_ELEPHANT,
                        _piece[BLACK_ELEPHANT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_CAT, STEP_SOUTH, to);
    moves[count] = Move(BLACK_CAT,
                        _piece[BLACK_CAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_short(BLACK_LION, LEAP_EAST, to);
    moves[count] = Move(BLACK_LION,
                        _piece[BLACK_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_WOLF, STEP_WEST, to);
    moves[count] = Move(BLACK_WOLF,
                        _piece[BLACK_WOLF],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_LION, STEP_WEST, to);
    moves[count] = Move(BLACK_LION,
                        _piece[BLACK_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_LION, STEP_NORTH, to);
    moves[count] = Move(BLACK_LION,
                        _piece[BLACK_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_PANTHER, STEP_SOUTH, to);
    moves[count] = Move(BLACK_PANTHER,
                        _piece[BLACK_PANTHER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_PANTHER, STEP_EAST, to);
    moves[count] = Move(BLACK_PANTHER,
                        _piece[BLACK_PANTHER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_PANTHER, STEP_NORTH, to);
    moves[count] = Move(BLACK_PANTHER,
                        _piece[BLACK_PANTHER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_TIGER, STEP_NORTH, to);
    moves[count] = Move(BLACK_TIGER,
                        _piece[BLACK_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_CAT, STEP_EAST, to);
    moves[count] = Move(BLACK_CAT,
                        _piece[BLACK_CAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step_black_rat(STEP_NORTH, to);
    moves[count] = Move(BLACK_RAT,
                        _piece[BLACK_RAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_TIGER, STEP_EAST, to);
    moves[count] = Move(BLACK_TIGER,
                        _piece[BLACK_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_DOG, STEP_EAST, to);
    moves[count] = Move(BLACK_DOG,
                        _piece[BLACK_DOG],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_CAT, STEP_WEST, to);
    moves[count] = Move(BLACK_CAT,
                        _piece[BLACK_CAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step_black_rat(STEP_WEST, to);
    moves[count] = Move(BLACK_RAT,
                        _piece[BLACK_RAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_WOLF, STEP_SOUTH, to);
    moves[count] = Move(BLACK_WOLF,
                        _piece[BLACK_WOLF],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_CAT, STEP_NORTH, to);
    moves[count] = Move(BLACK_CAT,
                        _piece[BLACK_CAT],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_DOG, STEP_SOUTH, to);
    moves[count] = Move(BLACK_DOG,
                        _piece[BLACK_DOG],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_DOG, STEP_NORTH, to);
    moves[count] = Move(BLACK_DOG,
                        _piece[BLACK_DOG],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_PANTHER, STEP_WEST, to);
    moves[count] = Move(BLACK_PANTHER,
                        _piece[BLACK_PANTHER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_short(BLACK_TIGER, LEAP_WEST, to);
    moves[count] = Move(BLACK_TIGER,
                        _piece[BLACK_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_short(BLACK_LION, LEAP_WEST, to);
    moves[count] = Move(BLACK_LION,
                        _piece[BLACK_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_WOLF, STEP_EAST, to);
    moves[count] = Move(BLACK_WOLF,
                        _piece[BLACK_WOLF],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_long(BLACK_LION, LEAP_SOUTH, to);
    moves[count] = Move(BLACK_LION,
                        _piece[BLACK_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_long(BLACK_TIGER, LEAP_SOUTH, to);
    moves[count] = Move(BLACK_TIGER,
                        _piece[BLACK_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_step(BLACK_DOG, STEP_WEST, to);
    moves[count] = Move(BLACK_DOG,
                        _piece[BLACK_DOG],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_short(BLACK_TIGER, LEAP_EAST, to);
    moves[count] = Move(BLACK_TIGER,
                        _piece[BLACK_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_long(BLACK_LION, LEAP_NORTH, to);
    moves[count] = Move(BLACK_LION,
                        _piece[BLACK_LION],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_long(BLACK_TIGER, LEAP_NORTH, to);
    moves[count] = Move(BLACK_TIGER,
                        _piece[BLACK_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  {
    int const valid = can_leap_long(BLACK_TIGER, LEAP_NORTH, to);
    moves[count] = Move(BLACK_TIGER,
                        _piece[BLACK_TIGER],
                        to,
                        _board[to]);
    count += valid;
  }
  return count;
}


#endif