import asyncio
import aiohttp
import csv
import matplotlib.pyplot as plt
import json

def daneCSV(plik):
    with open(plik, encoding='utf-8') as csvfile:
        dane = csv.DictReader(csvfile, delimiter=";")
        rok2021 = []
        rok2022 = []
        
        for rzad in dane:
            if rzad["Sposób prezentacji"] == "Analogiczny miesiąc poprzedniego roku = 100":
                if rzad["Rok"] == "2022":
                    rok2022.append(float(rzad["Wartość"].replace(",",".")))
                elif rzad["Rok"] == "2021":
                    rok2021.append(float(rzad["Wartość"].replace(",",".")))
                elif int(rzad["Rok"]) < 2021:
                    break
    return [rok2021, rok2022]
    
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
            s =0
            i =0
    return out

async def main():
    rok2021, rok2022 = daneCSV('inflacja.csv')
    async with aiohttp.ClientSession() as client:
        dolar2021 = await fetch(client, "https://api.nbp.pl/api/exchangerates/rates/a/usd/2021-01-01/2021-12-31/?format=json")
        dolar2022 = await fetch(client, "https://api.nbp.pl/api/exchangerates/rates/a/usd/2022-01-01/2022-12-31/?format=json")

    dolar2021 = jsonAvg(json.loads(dolar2021))
    dolar2022 = jsonAvg(json.loads(dolar2022))

    mies = [i+1 for i in range(12)]
    fig, axs = plt.subplots(2)
    axs[0].bar(mies, rok2021, width=1, color="blue", edgecolor="white", linewidth=0.7)
    axs[0].set(title='Inflacja w Polsce w 2021 r.',
               ylabel="Wzkaźnik inflacji względem poprzedniego miesiąca",
               xlabel="Miesiąc")
    axs[1].bar(mies, rok2022, width=1, color="blue", edgecolor="white", linewidth=0.7)
    axs[1].set(title="Inflacja w Polsce w 2022 r.",
               ylabel="Wzkaźnik inflacji względem poprzedniego miesiąca",
               xlabel="Miesiąc")
    
    for ax in fig.get_axes():
        ax.label_outer()

    plt.show()

asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()) # Bez tej linijki program zgłasza RuntimeError na Windowsie

asyncio.run(main())