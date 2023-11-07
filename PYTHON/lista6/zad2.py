import bs4
import asyncio
import urllib.request
import difflib


async def monitor(url):
    content = urllib.request.urlopen(url)
    dane = bs4.BeautifulSoup(content.read(), 'html.parser')

   
    while True:
        content_diff = urllib.request.urlopen(url)
        dane_diff = bs4.BeautifulSoup(content.read(), 'html.parser')

        lines = dane.prettify().split("\n")
        lines_diff = dane_diff.prettify().split("\n")

        print(difflib.Differ(dane.prettify(), dane_diff.prettify()))

        for i in range(min(len(lines), len(lines_diff))):
            if lines[i] != lines_diff[i]:
                print(lines_diff[i])

        
        dane = dane_diff
        await asyncio.sleep(10)
    return

asyncio.run(monitor("https://www.clocktab.com/"))
