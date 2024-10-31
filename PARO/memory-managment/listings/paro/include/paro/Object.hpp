#pragma once

#include <iostream>
#include <stdexcept>

struct Object
{
    Object(int a, int b, int c);
    ~Object();

    bool is_odd() const noexcept;
    int method() const noexcept;

    void risky_operation();

private:
    int a, b, c;
};

void store_result(int x);
