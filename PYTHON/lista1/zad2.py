def is_palindrom(text):
  text = filter(str.isalpha, text) #usuwanie innych znaków niż alfanumeryczne
  text = "".join(text).lower() #zmienianie wielkości liter
  text2= text[::-1]
  return text==text2

print(is_palindrom("kajak"))
print(is_palindrom("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrom("Míč omočím."))