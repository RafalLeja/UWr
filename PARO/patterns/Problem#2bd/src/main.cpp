#include <iostream>
#include "Document.hpp"

int main()
{
    Document pdfFile("PDF");
    pdfFile.addText("", {"Chapter 1", "trigonometry"});
    pdfFile.addTable("|", "|" , "|", {"Angle","0","30","45", "60", "90", "180"});
    pdfFile.addTable("|", "|" , "|", {"sin","0","1/2","sqrt(2)/2)", "sqrt(3)/2", "1", "0"});
    pdfFile.addTable("|", "|" , "|", {"cos","1","sqrt(3)/2)","sqrt(2)/2", "1/2", "0", "-1"});
    pdfFile.addTable("|", "|" , "|", {"tan","0","sqrt(3)/3","1", "sqrt(3)", "-", "0"});
    pdfFile.addTable("|", "|" , "|", {"cot","-","sqrt(3)","1", "sqrt(3)", "0", "-"});
    pdfFile.addText("", {"On the next chapter we'll learn how to use them.", "Stay tuned..."});
    std::cout << pdfFile.toStr() << std::endl;

    Document ePubFile("ePub");
    ePubFile.addText(">", {"Chapter 1", "trigonometry"});
    ePubFile.addTable("{", "," , "}", {"Angle","0","30","45", "60", "90", "180"});
    ePubFile.addTable("{", "," , "}", {"sin","0","1/2","sqrt(2)/2)", "sqrt(3)/2", "1", "0"});
    ePubFile.addTable("{", "," , "}", {"cos","1","sqrt(3)/2)","sqrt(2)/2", "1/2", "0", "-1"});
    ePubFile.addTable("{", "," , "}", {"tan","0","sqrt(3)/3","1", "sqrt(3)", "-", "0"});
    ePubFile.addTable("{", "," , "}", {"cot","-","sqrt(3)","1", "sqrt(3)", "0", "-"});
    ePubFile.addText(">", {"On the next chapter we'll learn how to use them.", "Stay tuned..."});
    std::cout << ePubFile.toStr() << std::endl;

    Document mobiFile("Mobi");
    mobiFile.addText("+", {"Chapter 1", "trigonometry"});
    mobiFile.addTable("{", "}{" , "}", {"Angle","0","30","45", "60", "90", "180"});
    mobiFile.addTable("{", "}{" , "}", {"sin","0","1/2","sqrt(2)/2)", "sqrt(3)/2", "1", "0"});
    mobiFile.addTable("{", "}{" , "}", {"cos","1","sqrt(3)/2)","sqrt(2)/2", "1/2", "0", "-1"});
    mobiFile.addTable("{", "}{" , "}", {"tan","0","sqrt(3)/3","1", "sqrt(3)", "-", "0"});
    mobiFile.addTable("{", "}{" , "}", {"cot","-","sqrt(3)","1", "sqrt(3)", "0", "-"});
    mobiFile.addText("+", {"On the next chapter we'll learn how to use them.", "Stay tuned..."});
   std::cout << mobiFile.toStr() << std::endl;
}
