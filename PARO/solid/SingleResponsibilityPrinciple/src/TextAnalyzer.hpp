#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

class TextAnalyzer
{
public:

    void run()
    {
        welcomeMsg();
        while(true)
        {
            printToUser("Gimme your text file!: ");
            auto filename = getTextFilenameFromUser();

            if (getChoiceFromUser("Wanna full analysis with summary in file?"))
                doFullAnalyze(filename);
            if (getChoiceFromUser("Wanna manual analysis on terminal?"))
                doManualAnalyze(filename);
            if (not getChoiceFromUser("Wanna analyze another file?"))
            {
                byeMsg();
                return;
            }
        }
    }

private:
    const std::string errorWhenFileDoesNotExist = "Hey dude! This file doesn't exist!\n";
    const std::string errorWhenUserPutInvalidInput = "Hey dude! Some problem with N or Y keys?\n";
    std::string filenameOfLastReadedFile;
    std::string textOfLastReadedFile;
    const std::string version = "1.0";

    void doManualAnalyze(std::string filename)
    {
        if (getChoiceFromUser("Wanna count words?"))
            printToUser(analyzeNumOfWords(filename));

        if (getChoiceFromUser("Wanna count letters?"))
            printToUser(analyzeNumOfLetters(filename));
    }

    void doFullAnalyze(std::string filename)
    {
        std::string outFilename = ("analysisOf" + filename);

        std::string resultOfAnalysis = analyzeNumOfWords(filename);
        resultOfAnalysis += analyzeNumOfLetters(filename);

        write2file(outFilename, resultOfAnalysis);
        printToUser("Analysis saved to file: " + outFilename + "\n");
    }

    std::string analyzeNumOfLetters(const std::string& filename)
    {
        auto text2analyze = getWholeText(filename);
        return "num of letters: " + std::to_string(countLetters(text2analyze)) + "\n";
    }

    std::string analyzeNumOfWords(const std::string& filename)
    {
        auto text2analyze = getWholeText(filename);
        return  "num of words: " + std::to_string(countWords(text2analyze)) + "\n";
    }

    void welcomeMsg()
    {
        printToUser("Welcome to Text Analyzer " + version + "!\n");
    }

    void byeMsg()
    {
        printToUser("Thanks for using Text Analyzer " + version + ".\n");
    }

    std::string getTextFilenameFromUser()
    {
        while(true)
        {
            std::string filename = readFromUser();
            if (isFileExisting(filename))
                return filename;

            printToUser(errorWhenFileDoesNotExist);
        }
    }

    bool getChoiceFromUser(std::string question)
    {
        std::string answer;
        while(true)
        {
            printToUser(question +  " (Y/N) :" );
            answer = readFromUser();
            if (1 == answer.size() && 'Y' == std::toupper(answer[0]))
            {
                return true;
            }
            if (1 == answer.size() && 'N' == std::toupper(answer[0]))
            {
                return false;
            }
            printToUser(errorWhenUserPutInvalidInput);

        }
    }

    void printToUser(std::string msg)
    {
        std::cout << msg;
    }

    std::string readFromUser()
    {
        std::string retVal;
        std::cin >> retVal;
        return retVal;
    }

    unsigned countLetters(const std::string& text2analyze)
    {
        unsigned retVal = 0;
        for (auto c : text2analyze)
        {
            if(std::isalpha(c))
                retVal++;
        }
        return retVal;
    }

    unsigned countWords(const std::string& text2analyze)
    {
        unsigned retVal = 0;
        bool isWordOngoing = false;
        for (auto c : text2analyze)
        {
            if(std::isalpha(c))
            {
                isWordOngoing = true;
            }

            else if(isWordOngoing)
            {
                retVal++;
                isWordOngoing = false;
            }

        }
        return retVal;
    }

    bool isFileExisting(std::string fileName)
    {
        std::ifstream infile(fileName);
        return infile.good();
    }

    void storeFileContent()
    {
        std::ifstream fileToRead(filenameOfLastReadedFile, std::ios::in);
        textOfLastReadedFile.clear();

        for (std::string line; std::getline(fileToRead, line); )
        {
            textOfLastReadedFile += line;
            textOfLastReadedFile += "\n";
        }
        fileToRead.close();
    }

    std::string getWholeText(std::string filename)
    {
        if(filenameOfLastReadedFile != filename && filename.size() > 0)
        {
            if(isFileExisting(filename))
            {
                filenameOfLastReadedFile = filename;
                storeFileContent();
            }
            else
            {
                throw std::invalid_argument("No file found");
            }
        }
        return textOfLastReadedFile;
    }

    void write2file(std::string filename, std::string what)
    {
        std::ofstream fileToWrite(filename, std::ios::out);
        if(fileToWrite)
        {
            fileToWrite << what;
            fileToWrite.close();
        }
        else
        {
            throw std::invalid_argument("Can't create a file: " + filename);
        }
    }
};

