# Rafał Leja 340879
# zadanie 4 lista 2 "upraszczanie"
# 12.10.2023


import random as r
import urllib.request

content = urllib.request.urlopen("https://www.gutenberg.org/files/31536/31536-0.txt").read().decode()

def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    tekst = tekst.replace(".", "")
    words = []
    for slowo in tekst.split(" "):
        if len(slowo.replace(",", "")) > dl_slowa:
            continue
        words.append(slowo)
        if len(words) > liczba_slow:
            for idx in range(len(words) - liczba_slow):
                words.pop(r.randrange(0, len(words)))

    output = " ".join(words) + "."
    
    return output.capitalize()

out = ""
for zdanie in content.split("."):
    out += uprosc_zdanie(zdanie, 8, 5) + " "

print(out)
