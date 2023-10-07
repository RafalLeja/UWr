# Rafał Leja 340879
# zadanie 4 lista 2 "upraszczanie"
import random as r


def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    tekst = tekst.replace(".", "")
    words = []
    output = ""
    for slowo in tekst.split(" "):
        if len(slowo.replace(",", "")) > dl_slowa:
            continue
        words.append(slowo)

    for idx in range(liczba_slow):
        words.pop(r.randrange(0, len(words)))

    output = " ".join(words) + "."
    
    return output
print(uprosc_zdanie("Ala ma kota. psa i rybke", 3, 2))
