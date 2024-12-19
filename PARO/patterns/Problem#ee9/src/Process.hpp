#pragma once
#include "Logger.hpp"

class Process
{
public:
    Process(std::unique_ptr<Logger> t, std::unique_ptr<Logger> f)
        :term(std::move(t)), file(std::move(f))
    {}

    void startup()
    {
        file->info("process started");
        auto answer = resolveQuestionOFLife();
        if (answer!= 42)
            file->error("Wrong answer. Autodestruction in 3.2.1...");
    }

private:
    int resolveQuestionOFLife()
    {
        int answerForQuestionOfLife = 0;
        term->debug("answerForQuestionOfLife initialized");
        for (int i = 0; i <= 42; i++)
            answerForQuestionOfLife++;
        term->debug("just wait a sec to know the answer about Life, the Universe, and Everything...");
        return  answerForQuestionOfLife;
    }

    std::unique_ptr<Logger> term;
    std::unique_ptr<Logger> file;
};
