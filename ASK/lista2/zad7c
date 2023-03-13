int32_t mask = x >> 31;             // przesunięcie arytmentyczne
return mask & (-x) + ~mask & x;     // dla x>= 0 mask == 0
                                    // dla x < 0 mask == F 