#pragma once

#include <vector>

enum DocumentType
{
    Table, Text
};

struct Content
{
    DocumentType type;
    vector<string> payload;
};


class Director
{
public:
    Director(Builder& b):builder(b)
    {}

    void construct(vector<Content> content)
    {
        for(auto it = content.begin(); it != content.end(); it++)
        {
            Content c = *it;
            if (c.type == Table)
                builder.addTable(c.payload);
            else if (c.type == Text)
                builder.addText(c.payload);
        }
    }
private:
    Builder& builder;
};
