# Rafał Leja 340879
# zadanie 2 lista 2 "sudan"
# 7.10.2023

mem = {
    "0|0|0" : 0
}

def sudan(n, x, y):
    if n == 0:
        return x + y
    if y == 0:
        return x
    return sudan(n-1, sudan(n, x, y-1), sudan(n, x, y-1) + y)

def sudanM(n, x, y):
    key = str(n) + "|" + str(x) + "|" + str(y)
    if key in mem:
        return mem[key]
    
    if n == 0:
        mem[key] = x + y
        return x + y
    if y == 0:
        mem[key] = x
        return x
    mem[key] = sudan(n-1, sudan(n, x, y-1), sudan(n, x, y-1) + y)
    return mem[key]

print(sudanM(1, 1, 3))
print(sudan(1, 1, 3))
