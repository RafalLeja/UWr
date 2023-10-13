# Rafał Leja 340879
# zadanie 5 lista 2 "kompresja"
# 12.10.2023

import urllib.request
content = urllib.request.urlopen("https://www.gutenberg.org/files/31536/31536-0.txt").read().decode()

def kompresja(slowo):
  out = []
  licznik = 1
  for idx in range(len(slowo)):
    if idx != len(slowo)-1:
      if slowo[idx] == slowo[idx+1]:
        licznik += 1
        continue
    out.append([slowo[idx], licznik])
    licznik = 1
  return out

def dekompresja(komp):
  out = ""
  for idx in range(len(komp)):
    print([komp[idx][0]]*komp[idx][1])
    out = out + "".join([komp[idx][0]]*komp[idx][1])
  return out

print(kompresja(content))    