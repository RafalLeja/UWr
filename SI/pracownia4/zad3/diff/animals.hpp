#include <iostream>

static uint32_t const BLACK = 0;
static uint32_t const WHITE = 1;

static uint32_t const BLACK_RAT = 0;
static uint32_t const WHITE_RAT = 1;
static uint32_t const BLACK_CAT = 2;
static uint32_t const WHITE_CAT = 3;
static uint32_t const BLACK_DOG = 4;
static uint32_t const WHITE_DOG = 5;
static uint32_t const BLACK_WOLF = 6;
static uint32_t const WHITE_WOLF = 7;
static uint32_t const BLACK_PANTHER = 8;
static uint32_t const WHITE_PANTHER = 9;
static uint32_t const BLACK_TIGER = 10;
static uint32_t const WHITE_TIGER = 11;
static uint32_t const BLACK_LION = 12;
static uint32_t const WHITE_LION = 13;
static uint32_t const BLACK_ELEPHANT = 14;
static uint32_t const WHITE_ELEPHANT = 15;
static uint32_t const NONE = 16;

static inline bool isWhite(uint32_t animal) {
    return (animal & 1) == WHITE;
}

static inline bool isBlack(uint32_t animal) {
    return (animal & 1) == BLACK;
}

static inline int strength(uint32_t animal) {
    return (animal >> 1);
}

static inline bool isEnemy(uint32_t a, uint32_t b) {
    return (isWhite(a) & isBlack(b)) | (isBlack(a) & isWhite(b));
}

static inline bool canAttack(uint32_t a, uint32_t b) {
    return (b == NONE) | 
    (isEnemy(a, b) & ((strength(a) >= strength(b))) 
        || ((strength(a) == 0) & (strength(b) == 7)));
}