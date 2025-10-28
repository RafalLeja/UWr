with open("notes.h", "w") as outfile:
    outfile.write("#include <avr/pgmspace.h>\n")
    outfile.write("static const uint16_t notes[] PROGMEM = {\n")
    for octave in range(2, 7):
        for note in range(12):
            n = ((octave - 4) * 12) + (note - 9)
            outfile.write(f"{int(440 * (2 ** (n / 12)))}, ")
    outfile.write("\n};")
