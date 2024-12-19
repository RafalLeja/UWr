#pragma once
#include <vector>
#include <string>
#include "Document.hpp"

class Builder
{
public:
    virtual ~Builder() = default;

    virtual void addTable(vector<string>) = 0;
    virtual void addText(vector<string>) = 0;

    Builder(string type):document(type)
    {}

    Document getDocument()
    {
        return document;
    }
protected:
    Document document;
};
