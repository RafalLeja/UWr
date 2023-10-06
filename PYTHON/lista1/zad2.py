# Rafał Leja 340879
# zadanie 2 lista 1 "palindrom"
# 6.10.2023

def is_palindrom(text):
  text = filter(str.isalpha, text) #usuwanie innych znaków niż alfanumeryczne
  text = "".join(text).lower() #zmienianie wielkości liter i łączenie do stringa
  text2= text[::-1] #odwracanie stringa
  return text==text2

print(is_palindrom("kajak"))
print(is_palindrom("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrom("Míč omočím."))