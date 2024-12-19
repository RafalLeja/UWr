#pragma once
#include <Builder.hpp>

class EPubBuilder: public Builder
{
public:
    EPubBuilder():Builder("ePub")
    {}


    void addTable(vector<string> v)
    {
        document.addTable("{", ",", "}", v);
    }

    void addText(vector<string> t)
    {
        document.addText(">", t);
    }
};
