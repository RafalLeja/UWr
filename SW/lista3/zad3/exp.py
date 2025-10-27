import math

n = 1024

with open("table.c", "w") as outfile:
    outfile.write("uint8_t exp[] = {\n")
    for i in range(n):
        outfile.write(f"{int(((i / n) ** 2.2) * 1024)},\n")
    outfile.write("}")
