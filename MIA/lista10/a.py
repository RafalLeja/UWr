n, d = map(int, input().split())
players = sorted(list(map(int, input().split())), reverse=True)
i = 0
j = len(players) - 1
wins = 0
while i <= j:
    # print(f"player {i}, power {players[i]}")
    rest = d // players[i]
    # print(f"needs {rest} players")
    if j - i < rest:
        break
    i += 1
    j -= rest
    # if rest != 0:
    #     players = players[1:-rest]
    # else:
    #     players = players[1:]
    wins += 1
    # print(players[i : j + 1])

print(wins)
