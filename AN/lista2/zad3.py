import itertools

# Funkcja do zamiany wartości w notacji dwójkowej na dziesiętną
def binary_to_decimal(binary_str):
    decimal = 0
    for digit in binary_str:
        decimal = decimal * 2 + int(digit)
    return decimal

# Możliwe wartości dla zmiennych c, e^-2, e^-3, e^-4, e^-5
variables = [0, 1]

# Inicjalizacja listy na przechowywanie wyników
results = []

# Generowanie wszystkich możliwych kombinacji zmiennych
for c in variables:
    for e_2 in variables:
        for e_3 in variables:
            for e_4 in variables:
                for e_5 in variables:
                    # Wyliczanie x na podstawie podanych wartości
                    x = (-1) ** c * 0.1 * 2 ** (e_2 - 2) * 2 ** (e_3 - 3) * 2 ** (e_4 - 4) * 2 ** (e_5 - 5)
                    results.append(x)

# Sortowanie wyników
results.sort()

# Wydrukowanie wyników
print("Znalezione liczby dziesiętne:")
for x in results:
    print(x)

# Obliczanie najmniejszego przedziału [A, B]
A = results[0]
B = results[-1]

print(f"Najmniejszy przedział [A, B] to [{A}, {B}]")
