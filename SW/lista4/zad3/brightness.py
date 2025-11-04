import math

N = 128
gamma = 2.2

brightness = []
for i in range(N):
    angle = math.pi * i / (N - 1)
    val = (math.sin(angle)) ** gamma
    brightness.append(round(val * 255))

brightness_full = brightness  # + brightness[::-1][1:-1]


with open("table.h", "w") as outfile:
    outfile.write("#include <avr/pgmspace.h>\n")
    outfile.write("static const uint8_t brightness[] PROGMEM = {\n")

    for i in range(0, len(brightness_full), 16):
        outfile.write(
            "  " + ", ".join(f"{v:3}" for v in brightness_full[i : i + 16]) + ","
        )
    outfile.write("};")
