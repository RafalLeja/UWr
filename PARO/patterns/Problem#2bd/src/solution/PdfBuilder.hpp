#pragma once
#include <Builder.hpp>

class PdfBuilder: public Builder
{
public:
    PdfBuilder():Builder("PDF")
    {}


    void addTable(vector<string> v)
    {
        document.addTable("|", "|", "|", v);
    }

    void addText(vector<string> t)
    {
        document.addText("", t);
    }
};
