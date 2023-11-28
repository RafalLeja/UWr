import csv
import matplotlib.pyplot as plt

with open('inflacja.csv', encoding="utf-8") as csvfile:
    dane = csv.DictReader(csvfile, delimiter=";")
    rok2021 = [[],[]]
    rok2022 = [[],[]]
    
    for rzad in dane:
        print(rzad.keys())
        if rzad["Sposób prezentacji"] == "Poprzedni miesi¹c = 100":
            if rzad["Rok"] == "2022":
                rok2022[0].insert(0, rzad["Miesi¹c"])
                rok2022[1].insert(1, float(rzad["Wartość"].replace(",",".")))
            elif rzad["Rok"] == "2021":
                rok2021[0].insert(0, rzad["Miesi¹c"])
                rok2021[1].insert(1, float(rzad["Wartość"].replace(",",".")))
            elif int(rzad["Rok"]) < 2021:
                break
    
    print(rok2021)
    fig, axs = plt.subplots(2)
    axs[0].plot(rok2021[0], rok2021[1])
    axs[0].set_title('Inflacja w Polsce w 2021 r.')
    axs[0].set(ylabel="Wzkaźnik inflacji względem poprzedniego miesiąca",
               xlabel="Miesiąc")
    axs[1].plot(rok2022[0], rok2022[1])
    axs[1].set_title("Inflacja w Polsce w 2022 r.")
    axs[1].set(ylabel="Wzkaźnik inflacji względem poprzedniego miesiąca",
               xlabel="Miesiąc")
    
    for ax in fig.get_axes():
        ax.label_outer()

    plt.show()