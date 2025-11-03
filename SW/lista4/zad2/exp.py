n = 900 - 200
max_value = 1024

with open("table.h", "w") as outfile:
    outfile.write("#include <avr/pgmspace.h>\n")
    outfile.write("static const uint16_t exp_table[] PROGMEM = {\n")
    for i in range(n):
        outfile.write(f"{int(((i / n) ** 2.2) * max_value)},\n")
    outfile.write("};")

    outfile.write("static const uint16_t lin_table[] PROGMEM = {\n")
    for i in range(n):
        outfile.write(f"{int((i / n) * max_value)},\n")
    outfile.write("};")
