with open("notes.c", "w") as outfile:
    outfile.write("int notes[] = {\n")
    for octave in range(2, 6):
        for note in range(12):
            n = ((octave - 4) * 12) + (note - 9)
            outfile.write(f"{int(440 * (2 ** (n / 12)))}, ")
    outfile.write("\n}")
