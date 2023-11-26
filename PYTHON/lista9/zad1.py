import csv
import matplotlib.pyplot as plt

with open('inflacja.csv', newline='') as csvfile:
    dane = csv.DictReader(csvfile, delimiter=";")
    rok2021 = [[],[]]
    rok2022 = [[],[]]
    
    for rzad in dane:
        if rzad["Sposób prezentacji"] == "Poprzedni miesi¹c = 100":
            if rzad["Rok"] == "2022":
                rok2022[0].insert(0, rzad["Miesi¹c"])
                rok2022[1].insert(1, float(rzad["Wartoœæ"].replace(",",".")))
            elif rzad["Rok"] == "2021":
                rok2021[0].insert(0, rzad["Miesi¹c"])
                rok2021[1].insert(1, float(rzad["Wartoœæ"].replace(",",".")))
            elif int(rzad["Rok"]) < 2021:
                break
    
    print(rok2021)
    plt.plot(rok2021[0], rok2021[1])
    plt.ylabel("Wzkaźnik inflacji względem poprzedniego miesiąca")
    plt.xlabel("Miesiąc")
    plt.show()