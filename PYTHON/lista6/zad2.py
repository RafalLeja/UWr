import bs4
import asyncio
import urllib.request
import difflib
import requests


async def monitor(url):
    content = urllib.request.urlopen(url)
    dane = bs4.BeautifulSoup(content.read(), 'html.parser')

    # dane = ""
    # for chunk in content.iter_content(chunk_size=128):
    #     dane += str(chunk)
   
    while True:
        content_diff = urllib.request.urlopen(url)
        dane_diff = bs4.BeautifulSoup(content_diff.read(), 'html.parser')

        # dane_diff = ""
        # for chunk in content_diff.iter_content(chunk_size=128):
        #     dane_diff += str(chunk)

        print(dane.prettify())

        lines = dane.prettify().split()
        lines_diff = dane_diff.prettify().split()

        # print(difflib.Differ(dane.prettify(), dane_diff.prettify()))

        for i in range(min(len(lines), len(lines_diff))):
            if lines[i] != lines_diff[i]:
                print(lines_diff[i])

        
        dane = dane_diff
        await asyncio.sleep(10)
    return

asyncio.run(monitor("http://randomcolour.com/"))
