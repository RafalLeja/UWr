# Rafał Leja 340879
# zadanie 2 lista 2 "sudan"
# 7.10.2023

def sudan(n, x, y):
    if n == 0:
        return x + y
    if y == 0:
        return x
    return sudan(n-1, sudan(n, x, y-1), sudan(n, x, y-1) + y)

print(sudan(1, 1, 3))
