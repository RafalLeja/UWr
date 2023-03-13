if (x != y) // bo x^y = 0
{
    *y = *y ^ *x;   // x=x y=x^y
    *x = *x ^ *y;   // x=(x^x)^y=0^y=y y=x^y
    *y = *y ^ *x;   // x=y y=x^y^y=x
}
