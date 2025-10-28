from mido import MidiFile

mid = MidiFile("./mario.MID")
key = 0
KEYS = {"C": 0, "C#": 1}
MAJOR = {0: 0, 1: 0, 2: 1, 3: 1, 4: 2, 5: 3, 6: 3, 7: 4, 8: 4, 9: 5, 10: 5, 11: 6}
MINOR = {0: 0, 1: 0, 2: 1, 3: 2, 4: 2, 5: 3, 6: 3, 7: 4, 8: 5, 9: 5, 10: 6, 11: 6}
DUR = {0: 0, 0.00104: 0, 0.12604: 1, 0.25104: 2}

next = ""
prev = ""
with open("melody.h", "w") as outfile:
    outfile.write("#include <avr/pgmspace.h>\n")
    outfile.write("static const uint8_t melody[] PROGMEM = {\n")
    ppqn = mid.ticks_per_beat
    print(ppqn)
    for msg in mid:
        print(msg)
        if msg.is_meta and msg.type == "key_signature":
            outfile.write(f"#define KEY {KEYS[msg.key]}\n")
            if hasattr(msg, "mode"):
                outfile.write(f"#define SCALE {msg.mode}\n")
            else:
                outfile.write("#define SCALE major\n")

        if msg.type == "note_on" and not msg.is_meta and msg.velocity > 0:
            c2 = msg.note - 36
            octave = (c2 // 12) - 1
            noteInKey = MAJOR[(c2 - key) % 12]
            duration = DUR[round(msg.time, 5)] + 1
            print(f"o: {octave}, n: {noteInKey}, t: {duration}")
            next = f"{format(octave, '0>2b')}{format(noteInKey, '0>3b')},\n"
            if prev != "":
                prev = f"0b0{format(duration, '0>2b')}" + prev
                outfile.write(prev)
            prev = next

    outfile.write("\n};")
