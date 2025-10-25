import math

n = 256

with open("table.c", "w") as outfile:
    outfile.write("uint8_t exp[] = {\n")
    for i in range(n):
        outfile.write(f"{int(1.02197**i)},\n")
    outfile.write("}")
