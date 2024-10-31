#include "Object.hpp"

#include <print>

Object::Object(int a, int b, int c) : a(a), b(b), c(c)
{
    std::println("create Object({}, {}, {})", a,b,c);
}

Object::  ~Object()
{
    std::println("delete Object({}, {}, {})", a,b,c);
}

bool Object::is_odd() const noexcept { return c % 2; }
int Object::method() const noexcept { return a - 1 * a + 7; }

void Object::risky_operation()
{
    throw std::runtime_error("The risk is too great to handle!");
    this->a = 2 * b + c;
}

void store_result(int x){}
