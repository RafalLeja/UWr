# Rafał Leja 340879
# zadanie 3 "indeks"
# 8.11.2023

import urllib.request
import bs4
import re
import multiprocessing as mp

def index(urls):
  with mp.Pool() as p:
    idx = dict(p.map(wordDict, urls))
  return idx

def wordDict(url):
  html = urllib.request.urlopen(url)
  soup = bs4.BeautifulSoup(html.read().decode(), 'html.parser')

  wordCount = {}

  words = soup.get_text()
  words = re.split(" |\n", words)
  for word in words:
    word = re.sub('[^A-Za-zżźćńółęąśŻŹĆĄŚĘŁÓŃ]+', '', word)
    word = word.lower().replace("\n", "")
    if word in wordCount:
      wordCount[word] += 1
    else:
      wordCount[word] = 1
  
  del wordCount['']
  wordCount = dict(sorted(wordCount.items(), key= lambda item: item[1], reverse=True))

  return [url, wordCount]

def search(index, word):
  max = 0
  maxUrl = "brak wyników"
  for url in index.keys():
    allWords = sum(index[url].values())
    if word in index[url].keys():
      if max < (index[url][word]/allWords):
        max = index[url][word]/allWords
        maxUrl = url
  
  return maxUrl

chlopiIndex = index(["https://wolnelektury.pl/katalog/lektura/chlopi-czesc-pierwsza-jesien.html",
                  "https://wolnelektury.pl/katalog/lektura/reymont-chlopi-zima.html",
                  "https://wolnelektury.pl/katalog/lektura/chlopi-czesc-trzecia-wiosna.html",
                  "https://wolnelektury.pl/katalog/lektura/chlopi-czesc-czwarta-lato.html"])

print(search(chlopiIndex, "jagusia"))