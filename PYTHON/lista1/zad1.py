# Rafał Leja 340879
# zadanie 1 lista 1 "vat"
# 6.10.2023

zakupy = [0.1, 0.1, 0.1, 0.1, 0.1, 10]

def vat_faktura(lista):
  return sum(lista) * 0.23

def vat_paragon(lista):
  vat = 0.0;
  for x in lista:
    vat += x*0.23
  return vat

print(vat_faktura(zakupy))
print(vat_paragon(zakupy))
print(vat_faktura(zakupy) == vat_paragon(zakupy))