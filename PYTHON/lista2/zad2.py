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
    #print("[ sudanM(" + str(n) + ", " + str(x) + ", " + str(y) + ")\n\t")
    key = str(n) + "|" + str(x) + "|" + str(y)
    if key in mem:
        return mem[key]
    if n == 0:
        mem[key] = x + y
        return x + y
    if y == 0:
        mem[key] = x
        return x
    mem[key] = sudanM(n-1, sudanM(n, x, y-1), sudanM(n, x, y-1) + y)
    return mem[key]

# największe sensowne wywołanie sudan dla n=2 i n=3
print("sudan:\n    " +
str(sudan(2, 1, 2)) + 
"\n    " +
str(sudan(3, 1, 1)))

# największe sensowne wywołanie sudanM dla n=2 i n=3
print("sudanM:\n    " +
str(sudanM(2, 5, 2)) + 
"\n    " +
str(sudanM(3, 1, 1)))