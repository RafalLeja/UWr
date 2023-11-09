# Rafał Leja 340879
# zadanie 1 C lista 5 "Wyrażenie"
# 02.11.2023

class VariableNotFoundException(Exception):
    pass

class Wyrazenie:
    def oblicz(self, zmienne):
        raise NotImplementedError("Metoda oblicz() musi być zaimplementowana w podklasach.")
    
    def pochodna(self, zmienna):
        raise NotImplementedError("Metoda pochodna() musi być zaimplementowana w podklasach.")  

    def __str__(self):
        raise NotImplementedError("Metoda __str__() musi być zaimplementowana w podklasach.")

    def __add__(self, w2):
        return Dodaj(self, w2)

    def __mul__(self, w2):
        return Razy(self, w2)

class Stala(Wyrazenie):
    def __init__(self, wartosc):
        self.wartosc = wartosc

    def oblicz(self, zmienne):
        return self.wartosc
    
    def pochodna(self, zmienna):
        return Stala(0)

    def __str__(self):
        return str(self.wartosc)

class Zmienna(Wyrazenie):
    def __init__(self, nazwa):
        self.nazwa = nazwa

    def oblicz(self, zmienne):
        if self.nazwa in zmienne:
            return zmienne[self.nazwa]
        raise VariableNotFoundException(f"Zmienna '{self.nazwa}' nie została znaleziona w słowniku zmiennych.")
    
    def pochodna(self, zmienna):
        if self.nazwa == zmienna:
            return Stala(1)  # Pochodna zmiennej względem samej siebie to 1
        else:
            return Stala(0)  # Pochodna względem innej zmiennej to zero

    def __str__(self):
        return self.nazwa
    
class Dodaj(Wyrazenie):
    def __init__(self, wyr1, wyr2):
        self.wyr1 = wyr1
        self.wyr2 = wyr2

    def oblicz(self, zmienne):
        return self.wyr1.oblicz(zmienne) + self.wyr2.oblicz(zmienne)
    
    def pochodna(self, zmienna):
        return self.wyr1.pochodna(zmienna) + self.wyr2.pochodna(zmienna)

    def __str__(self):
        return f"({self.wyr1} + {self.wyr2})"
    
class Odejmij(Wyrazenie):
    def __init__(self, wyr1, wyr2):
        self.wyr1 = wyr1
        self.wyr2 = wyr2

    def oblicz(self, zmienne):
        return self.wyr1.oblicz(zmienne) - self.wyr2.oblicz(zmienne)
    
    def pochodna(self, zmienna):
        return self.wyr1.pochodna(zmienna) - self.wyr2.pochodna(zmienna)

    def __str__(self):
        return f"({self.wyr1} - {self.wyr2})"

class Razy(Wyrazenie):
    def __init__(self, wyr1, wyr2):
        self.wyr1 = wyr1
        self.wyr2 = wyr2

    def oblicz(self, zmienne):
        return self.wyr1.oblicz(zmienne) * self.wyr2.oblicz(zmienne)
    
    def pochodna(self, zmienna):
        return self.wyr1 * self.wyr2.pochodna(zmienna) + self.wyr2 * self.wyr1.pochodna(zmienna)

    def __str__(self):
        return f"({self.wyr1} * {self.wyr2})"

class Podziel(Wyrazenie):
    def __init__(self, wyr1, wyr2):
        self.wyr1 = wyr1
        self.wyr2 = wyr2

    def oblicz(self, zmienne):
        return self.wyr1.oblicz(zmienne) / self.wyr2.oblicz(zmienne)
    
    def pochodna(self, zmienna):
        return  (self.wyr2 * self.wyr1.pochodna(zmienna) - self.wyr1 * self.wyr2.pochodna(zmienna)) / Razy(self.wyr2, self.wyr2)

    def __str__(self):
        return f"({self.wyr1} / {self.wyr2})"

wyrazenie = Razy(Dodaj(Zmienna("x"), Stala(2)), Zmienna("y"))
print(wyrazenie)

zmienne = {"x": 3, "y": 4}
wynik = wyrazenie.oblicz(zmienne)
print(wynik)

nowe_wyrazenie = (wyrazenie + Stala(5)) * Stala(2)
print(nowe_wyrazenie)

wynik_nowego = nowe_wyrazenie.oblicz(zmienne)
print(wynik_nowego)

funkcja = Razy(Dodaj(Zmienna("x"), Stala(2)), Zmienna("y"))
print(f"f(x) = {funkcja}")

pochodna_po_x = funkcja.pochodna("x")
print(f"f'(x) = {pochodna_po_x}")

pochodna_po_y = funkcja.pochodna("y")
print(f"f'(y) = {pochodna_po_y}")
