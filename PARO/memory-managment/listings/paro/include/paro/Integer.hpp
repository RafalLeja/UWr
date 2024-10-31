#pragma once

class Integer
{
    char name;
public:
    explicit Integer(char name = 'A');
    ~Integer();

    Integer(const Integer&) = delete;
    Integer& operator=(const Integer&) = delete;
};
