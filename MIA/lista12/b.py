def main():
    t = int(input())

    for test in range(t):
        n = int(input())
        arr = map(int, input().split())

        numbers = {e: 0 for e in range(1, n + 1)}
        for a in arr:
            while a > 1:
                if a <= n:
                    numbers[a] += 1
                a = a // 2
            numbers[1] += 1

        # print(numbers)
        yes = 1
        for a in range(n, 1, -1):
            if numbers[a] == 0:
                yes = 0
                break
            else:
                # print("removing", a)
                numbers[a] -= 1
                while a > 1:
                    a = a // 2
                    numbers[a] -= 1

        if yes == 0:
            print("NO")
        else:
            print("YES")


if __name__ == "__main__":
    main()
