#pragma once

#include <iostream>
#include <string>
#include <vector>

class Document
{
public:
    Document(std::string type)
    {
        document = "<" + type + " header>";
    }

    void addTable(std::string begin, std::string separator, std::string end,  std::vector<std::string> values)
    {
        document += "\n" + begin;
        for(auto value: values)
        {
            document += value + separator;
        }
        document = document.substr(0, document.size()-separator.size());
        document += end;
    }

    void addText(std::string begin, std::vector<std::string> text)
    {
        for (auto line: text)
            document += "\n" + begin + line;
    }

    std::string toStr()
    {
        return document;
    }

private:
    std::string document;
};
