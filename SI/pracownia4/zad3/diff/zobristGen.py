import random

outFile = open("zobrist.hpp", 'w')

ANIMALS = ["RAT", "CAT", "DOG", "WOLF", "PANTHER", "TIGER", "LION", "ELEPHANT", "TURN"]
COLORS = ["BLACK", "WHITE"]

outFile.write("#include <iostream>\n\n")
outFile.write("static uint64_t const zobristTable[17][64] =\n{")
for i in range(17):
    outFile.write("\n    { " + "// " + COLORS[i % 2] + "_" + ANIMALS[i // 2 ] + "\n")
    for j in range(64):
        outFile.write("        " + hex(random.getrandbits(64)) + "ull,\n")
    outFile.write("    },")

outFile.write("\n};\n")