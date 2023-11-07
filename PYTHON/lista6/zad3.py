import urllib
import bs4
import re

def index(urls):
  dict = {}

  for url in urls:
    html = urllib.request.urlopen(url)
    soup = bs4.BeautifulSoup(html.read(), 'html.parser')

    wordCount = {}

    words = soup.get_text()
    words = re.split(" |\n", words)
    for word in words:
      word = re.sub('[^A-Za-z]+', '', word)
      word = word.lower().replace("\n", "")
      if word in wordCount:
        wordCount[word] += 1
      else:
        wordCount[word] = 1
    
    del wordCount['']
    dict[url] = wordCount

  return dict

def search(index, word):
  max = 0
  maxUrl = ""
  for url in index.keys():
    allWords = sum(index[url].values())
    if word in index[url].keys():
      if max < (index[url][word]/allWords):
        max = index[url][word]
        maxUrl = url
  
  return url

chlopiIndex = index(["https://wolnelektury.pl/katalog/lektura/chlopi-czesc-pierwsza-jesien.html",
                  "https://wolnelektury.pl/katalog/lektura/reymont-chlopi-zima.html",
                  "https://wolnelektury.pl/katalog/lektura/chlopi-czesc-trzecia-wiosna.html",
                  "https://wolnelektury.pl/katalog/lektura/chlopi-czesc-czwarta-lato.html"])

print(search(chlopiIndex, "jagusia"))