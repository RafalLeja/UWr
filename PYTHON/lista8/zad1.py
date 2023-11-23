# klucz API do accuweather należy umieścic w pliku api.key
# Rafał Leja
# 22.11.2023

import asyncio
import aiohttp
import json
from urllib.parse import quote

async def fetch(client):
  async with client.get('https://lldev.thespacedevs.com/2.2.0/launch/upcoming/') as resp:
    assert resp.status == 200
    return await resp.text()

async def fetchWTHR(client, keyFile, query):
  # wyłapywanie błędu braku pliku
  try:
    f = open(keyFile, "r")
    key = f.read()
    searchUrl = "http://dataservice.accuweather.com/locations/v1/cities/autocomplete"
    forecastUrl = "http://dataservice.accuweather.com/forecasts/v1/hourly/1hour/"
    searchUrl += "?apikey=" + key + "&q=" + quote(query) + "&language=pl-pl"
    # Wysyłamy zapytanie o wyszukanie miasta o nazwie query
    async with client.get(searchUrl) as searchResp:
      assert searchResp.status == 200
      searchData = json.loads(await searchResp.text())
    # z odpowiedzi wyciągamy id miasta
    cityKey = searchData[0]["Key"]
    forecastUrl += cityKey + "?apikey=" + key + "&language=pl-pl&details=false&metric=true"
    # wysyłamy zapytanie o prognoze dla danego miasta po id
    async with client.get(forecastUrl) as forecastResp:
      assert forecastResp.status == 200
      forecastData = json.loads(await forecastResp.text())
    # zwracamy słownik z odpowiedznimi danymi
    outDict = {"Status" : "OK",
              "Name" : searchData[0]["LocalizedName"],
              "DateTime" : forecastData[0]["DateTime"],
              "Desc" : forecastData[0]["IconPhrase"],
              "PP" : forecastData[0]["PrecipitationProbability"],
              "Temp" : forecastData[0]["Temperature"]["Value"]}
  except:
    outDict = {"Status" : "No key file"}
  return outDict

async def main():
  async with aiohttp.ClientSession() as client:
    htmlRKT = await fetch(client)
    dataWTHR = await fetchWTHR(client, "api.key", "Wrocław")
    dataRKT = json.loads(htmlRKT)
    printLaunch(dataRKT)
    printWeather(dataWTHR)

  return 0

def printWeather(data):
  if data["Status"] == "OK":
    print(
      f'''Temperatura teraz w mieście {data["Name"]} to {data["Temp"]},
      {data["Desc"]}, prawdopodobieństwo opadów {data["PP"]}%'''
    )
  else:
    print("Brak klucza")

def printLaunch(data):
  nextLaunch = data["results"][0]
  print(
  f'''Następny lot w kosmos odbędzie się {nextLaunch["window_start"]}, 
  z {nextLaunch["pad"]["location"]["name"]}. Rakieta nośna to {nextLaunch["rocket"]["configuration"]["full_name"]}.''')

# asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()) # Bez tej linijki program zgłasza RuntimeError na Windowsie
asyncio.run(main())