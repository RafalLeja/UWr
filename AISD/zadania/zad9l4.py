def LCIS(arr1, arr2):
    if len(arr1) < len(arr2):
        arr1, arr2 = arr2, arr1

    n = len(arr1)
    m = len(arr2)
    
    f = [[0 for i in range(m)] for j in range(n)]
    pre = [[0 for i in range(m)] for j in range(n)]
    for i in range(n):
        fmax = 0
        pos = 0

        for j in range(m):
            f[i][j] = f[i - 1][j]
            pre[i][j] = pre[i - 1][j]

            if (arr1[i] == arr2[j]):
                if (fmax + 1 > f[i][j]):
                    f[i][j] = fmax + 1
                    pre[i][j] = pos

            if (arr1[i] > arr2[j]):
                if (f[i-1][j] > fmax):
                    fmax = f[i-1][j]
                    pos = j

    res = 0
    last = 0

    for j in range(m):
        if (f[-1][j] > res):
            res = f[n-1][j]
            last = j

    out = []
    i = n-2
    j = last
    while (i >= 0 and j >= 0):
        print(i, j, pre[i][j])
        if f[i][j] != f[i+1][j]:
            out.append(arr2[j])
            j = pre[i+1][j]

        i -= 1

    out.reverse()

    return out

# Driver Code
if __name__ == "__main__":
	
	arr1 = [2, 3, 1]
	arr2 = [1, 3, 2]

	print(LCIS(arr1, arr2))