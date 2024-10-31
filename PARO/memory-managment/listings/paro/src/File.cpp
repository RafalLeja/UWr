#include "File.h"

void print_file(std::FILE* file)
{
    if (not file)
        return;
    char buffer[1024];
    while (std::fgets(buffer, sizeof(buffer), file))
        std::fputs(buffer, stdout);
}
