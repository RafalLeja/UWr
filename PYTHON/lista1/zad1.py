

def vat_faktura(lista):
  return sum(lista) * 0.23

def vat_paragon(lista):
  vat = 0.0;
  for x in lista:
    vat += x*0.23
  return vat

print(vat_faktura([5.0, 2.0, 3.0, 4.3, 0.1]))
print(vat_paragon([5.0, 2.0, 3.0, 4.3, 0.1]))