from mido import MidiFile

mid = MidiFile("./mario.MID")
KEY = 0
MAJOR = {0: 0, 1: 0, 2: 1, 3: 1, 4: 2, 5: 3, 6: 3, 7: 4, 8: 4, 9: 5, 10: 5, 11: 6}
MINOR = {0: 0, 1: 0, 2: 1, 3: 2, 4: 2, 5: 3, 6: 3, 7: 4, 8: 5, 9: 5, 10: 6, 11: 6}


with open("melody.h", "w") as outfile:
    outfile.write("#include <avr/pgmspace.h>\n")
    outfile.write("static const uint8_t melody[] PROGMEM = {\n")
    for msg in mid:
        if msg.type == "note_on" and not msg.is_meta:
            c2 = msg.note - 36 + 12
            octave = c2 // 12
            noteInKey = MAJOR[(c2 - KEY) % 12]
            outfile.write(
                f"0b001{format(octave, '0<2b')}{format(noteInKey, '0<3b')},\n"
            )

    outfile.write("\n};")
