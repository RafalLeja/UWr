# Rafał Leja
# lista 9 "wykresy"
# 28/11/2023

import asyncio
import aiohttp
import csv
import matplotlib.pyplot as plt
import json
from statsmodels.tsa.statespace.sarimax import SARIMAX

def daneCSV(plik):
    with open(plik, encoding='utf-8') as csvfile:
        dane = csv.DictReader(csvfile, delimiter=";")
        rok = "2022"
        daneInf = []
        daneRok = []

        for rzad in dane:
            if rzad["Rok"] == "2023":
                continue

            if rzad["Sposób prezentacji"] == "Analogiczny miesiąc poprzedniego roku = 100":
                if rzad["Rok"] == rok:
                    daneRok.append(float(rzad["Wartość"].replace(",",".")))
                else:
                    rok = rzad["Rok"]
                    daneInf.append(daneRok)
                    daneRok = [float(rzad["Wartość"].replace(",","."))]
        daneInf.append(daneRok)
    return daneInf
    
async def fetch(client, url):
  async with client.get(url) as resp:
    assert resp.status == 200
    return await resp.text()

def jsonAvg(dane):
    mies = "01"
    out = []
    i = 0
    s = 0
    for n in dane["rates"]:
        if n["effectiveDate"][5:7] == mies:
            i +=1
            s +=n["mid"]
        else:
            mies = n["effectiveDate"][5:7]
            out.append(s/i)
            s =n["mid"]
            i =1
    out.append(s/i)
    return out

def flat(arr):
    out = []
    for i in arr:
        for j in i:
            out.append(j)
    return out

async def main():
    daneInf = daneCSV('inflacja.csv')
    async with aiohttp.ClientSession() as client:
        dolar2021 = await fetch(client, "https://api.nbp.pl/api/exchangerates/rates/a/usd/2021-01-01/2021-12-31/?format=json")
        dolar2022 = await fetch(client, "https://api.nbp.pl/api/exchangerates/rates/a/usd/2022-01-01/2022-12-31/?format=json")

    dolar2021 = jsonAvg(json.loads(dolar2021))
    dolar2022 = jsonAvg(json.loads(dolar2022))

    mies = [i+1 for i in range(12)]

    fig, (ax1a, ax2a, ax3) = plt.subplots(3)

    fig.suptitle("Inflacja w Polsce względem analogicznego miesiąca zeszłego roku")
    l1 = ax1a.bar(mies, daneInf[1], width=1, color="blue", edgecolor="white", linewidth=0.7)
    ax1a.set(ylim=(95,120),
             title='2021',
             ylabel="%",
             xlabel="Miesiąc")
    
    ax1b = ax1a.twinx()
    l2, = ax1b.plot(mies, dolar2021, color="red")
    ax1b.set(ylabel="USD/PLN",
             ylim=(3.7,5))
    ax1a.legend((l1, l2), ('współczynnik inflacji', "kurs USD/PLN"), loc='upper left')
    
    l3 = ax2a.bar(mies, daneInf[0], width=1, color="blue", edgecolor="white", linewidth=0.7)
    ax2a.set(ylim=(95,120),
               title="2022",
               ylabel="%",
               xlabel="Miesiąc")
    
    ax2b = ax2a.twinx()
    l4, = ax2b.plot(mies, dolar2022, color="red")
    ax2b.set(ylabel="USD/PLN",
             ylim=(3.7,5))
    ax2a.legend((l3, l4), ('współczynnik inflacji', "kurs USD/PLN"), loc='upper left')

    daneFlat = flat(daneInf)
    model = SARIMAX(daneFlat, order=(1, 1, 1), seasonal_order=(0, 0, 0, 0))
    model_fit = model.fit(method="lbfgs")
    future = model_fit.predict(1, 12)
    print(future)
    ax3.bar(mies, future, width=1, color="blue", edgecolor="white", linewidth=0.7)
    ax3.set(ylim=(95,120),
               title="2023",
               ylabel="%",
               xlabel="Miesiąc")

    for ax in fig.get_axes():
        ax.label_outer()

    plt.show()

asyncio.run(main())