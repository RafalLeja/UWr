# klucz API do accuweather należy umieścic w pliku apiKey.txt

import asyncio
import aiohttp
import json
from urllib.parse import quote

async def fetch(client):
  async with client.get('https://lldev.thespacedevs.com/2.2.0/launch/upcoming/') as resp:
    assert resp.status == 200
    return await resp.text()

async def fetchWTHR(client, keyFile, query):
  f = open(keyFile, "r")
  if f == False:
    raise FileNotFoundError
  key = f.read()
  searchUrl = "http://dataservice.accuweather.com/locations/v1/cities/autocomplete"
  forecastUrl = "http://dataservice.accuweather.com/forecasts/v1/hourly/1hour/"
  searchUrl += "?apikey=" + key + "&q=" + quote(query) + "&language=pl-pl"
  async with client.get(searchUrl) as searchResp:
    assert searchResp.status == 200
    #  await searchResp.text()
    searchData = json.loads(await searchResp.text())
  cityKey = searchData[0]["Key"]
  forecastUrl += cityKey + "?apikey=" + key + "&language=pl-pl&details=false&metric=true"
  async with client.get(forecastUrl) as forecastResp:
    assert forecastResp.status == 200
    forecastData = json.loads(await forecastResp.text())
  outDict = {"Name" : searchData[0]["LocalizedName"],
             "DateTime" : forecastData[0]["DateTime"],
             "Desc" : forecastData[0]["IconPhrase"],
             "PP" : forecastData[0]["PrecipitationProbability"],
             "Temp" : forecastData[0]["Temperature"]["Value"]}
  return outDict
  
  
  

async def main():
  async with aiohttp.ClientSession() as client:
    htmlRKT = await fetch(client)
    dataWTHR = await fetchWTHR(client, "apiKEY.txt", "Wrocław")
    dataRKT = json.loads(htmlRKT)
    printLaunch(dataRKT)
    printWeather(dataWTHR)

  return 0

def printWeather(data):
  print(
    f'''Temperatura teraz w mieście {data["Name"]} to {data["Temp"]},
    {data["Desc"]}, prawdopodobieństwo opadów {data["PP"]}%'''
  )

def printLaunch(data):
  nextLaunch = data["results"][0]
  print(
  f'''Następny lot w kosmos odbędzie się {nextLaunch["window_start"]}, 
  z {nextLaunch["pad"]["location"]["name"]}. Rakieta nośna to {nextLaunch["rocket"]["configuration"]["full_name"]}.''')

asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy()) # Bez tej linijki program zgłasza RuntimeError
asyncio.run(main())