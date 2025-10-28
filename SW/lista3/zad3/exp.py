n = 1024

with open("table.h", "w") as outfile:
    outfile.write("#include <avr/pgmspace.h>\n")
    outfile.write("static const uint16_t exp_table[] PROGMEM = {\n")
    for i in range(n):
        outfile.write(f"{int(((i / n) ** 2.2) * 1024)},\n")
    outfile.write("};")
