tests = int(input())

def ww(r, l):
    s2 = (r//2) - ((l-1) // 2)
    s3 = (r//3) - ((l-1) // 3)
    s5 = (r//5) - ((l-1) // 5)
    s7 = (r//7) - ((l-1) // 7)
    s2s3 = (r//(2*3)) - ((l-1)//(2*3))
    s2s5 = (r//(2*5)) - ((l-1)//(2*5))
    s2s7 = (r//(2*7)) - ((l-1)//(2*7))
    s3s5 = (r//(3*5)) - ((l-1)//(3*5))
    s3s7 = (r//(3*7)) - ((l-1)//(3*7))
    s5s7 = (r//(5*7)) - ((l-1)//(5*7))
    s2s3s5 = (r//(2*3*5)) - ((l-1)//(2*3*5))
    s2s3s7 = (r//(2*3*7)) - ((l-1)//(2*3*7))
    s2s5s7 = (r//(2*5*7)) - ((l-1)//(2*5*7))
    s3s5s7 = (r//(3*5*7)) - ((l-1)//(3*5*7))
    s2s3s5s7 = (r//(2*3*5*7)) - ((l-1)//(2*3*5*7))
    # print( s2 + s3 + s5 + s7)
    # print(- s2s3 - s2s5 - s2s7 - s3s5 -s3s7 - s5s7 )
    # print(+ s2s3s5 + s2s3s7 +s3s5s7     )
    return s2 + s3 + s5 + s7- s2s3 - s2s5 - s2s7 - s3s5 -s3s7 - s5s7 + s2s3s5 + s2s3s7 + s2s5s7 +s3s5s7     - s2s3s5s7

for test in range(tests):
    l, r = list(map(int, input().split(" ")))
    # print(l , r)
    total = r - l +1
    print(total -ww(r,l))
