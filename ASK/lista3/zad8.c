#include <stdint.h>

int32_t float2int(int32_t f)
{
    int32_t s = f >> 31;
    int32_t e = (f >> 23 & 255) - 127;
    uint32_t m = f << 8 | 0x80000000;

}