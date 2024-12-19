#pragma once
#include <Builder.hpp>

class MobiBuilder: public Builder
{
public:
    MobiBuilder():Builder("Mobi")
    {}


    void addTable(vector<string> v)
    {
        document.addTable("{", "}{", "}", v);
    }

    void addText(vector<string> t)
    {
        document.addText("+", t);
    }
};
