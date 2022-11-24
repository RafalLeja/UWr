krazki = 6; licznik = 0

A = [x for x in range(krazki, 0, -1)]; B = []; C = []

def prt(A, B, C, krazki):
    a = A.copy(); b = B.copy(); c = C.copy()
    while len(a) < krazki: a.append('|')
    while len(b) < krazki: b.append('|')
    while len(c) < krazki: c.append('|')
    for x in range(krazki - 1, -1, -1):
        print(str(a[x]) + "    " + str(b[x]) + "    " + str(c[x]) + "    ")
    print("-------------")


if not krazki % 2:      #parzyste       AB AC BC
    while len(C) < krazki:
        licznik += 3
        if len(A) and (not B or A[len(A) - 1] < B[len(B) - 1]): B.append(A[len(A) - 1]); A.pop(); prt(A, B, C, krazki)
        else: A.append(B[len(B) - 1]); B.pop(); prt(A, B, C, krazki)

        if A and (not C or A[len(A) - 1] < C[len(C) - 1]): C.append(A[len(A) - 1]); A.pop(); prt(A, B, C, krazki)
        else: A.append(C[len(C) - 1]); C.pop(); prt(A, B, C, krazki)

        if B and (not C or B[len(B) - 1] < C[len(C) - 1]): C.append(B[len(B) - 1]); B.pop(); prt(A, B, C, krazki)
        else: B.append(C[len(C) - 1]); C.pop(); prt(A, B, C, krazki)

else:                   #nieparzyste    AC AB BC
    while len(C) < krazki:
        licznik += 3
        if A and (not C or A[len(A) - 1] < C[len(C) - 1]): C.append(A[len(A) - 1]); A.pop(); prt(A, B, C, krazki)
        else: A.append(C[len(C) - 1]); C.pop(); prt(A, B, C, krazki)

        if len(A) and (not B or A[len(A) - 1] < B[len(B) - 1]): B.append(A[len(A) - 1]); A.pop(); prt(A, B, C, krazki)
        else: A.append(B[len(B) - 1]); B.pop(); prt(A, B, C, krazki)

        if B and (not C or B[len(B) - 1] < C[len(C) - 1]): C.append(B[len(B) - 1]); B.pop(); prt(A, B, C, krazki)
        else: B.append(C[len(C) - 1]); C.pop(); prt(A, B, C, krazki)

print(licznik)