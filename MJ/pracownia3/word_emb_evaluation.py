# -*- encoding: utf8 -*-

from collections import defaultdict as dd
import numpy as np
import random
import sys

random.seed(42)

clusters_txt = '''
piśmiennicze: pisak flamaster ołówek długopis pióro
małe_ssaki: mysz szczur chomik łasica kuna bóbr
okręty: niszczyciel lotniskowiec trałowiec krążownik pancernik fregata korweta
lekarze: lekarz pediatra ginekolog kardiolog internista geriatra
zupy: rosół żurek barszcz
uczucia: miłość przyjaźń nienawiść gniew smutek radość strach
działy_matematyki: algebra analiza topologia logika geometria 
budynki_sakralne: kościół bazylika kaplica katedra świątynia synagoga zbór
stopień_wojskowy: chorąży podporucznik porucznik kapitan major pułkownik generał podpułkownik
grzyby_jadalne: pieczarka borowik gąska kurka boczniak kania
prądy_filozoficzne: empiryzm stoicyzm racjonalizm egzystencjalizm marksizm romantyzm
religie: chrześcijaństwo buddyzm islam prawosławie protestantyzm kalwinizm luteranizm judaizm
dzieła_muzyczne: sonata synfonia koncert preludium fuga suita
cyfry: jedynka dwójka trójka czwórka piątka szóstka siódemka ósemka dziewiątka
owady: ważka biedronka żuk mrówka mucha osa pszczoła chrząszcz
broń_biała: miecz topór sztylet nóż siekiera
broń_palna: karabin pistolet rewolwer fuzja strzelba
komputery: komputer laptop kalkulator notebook
kolory: biel żółć czerwień błękit zieleń brąz czerń
duchowny: wikary biskup ksiądz proboszcz rabin pop arcybiskup kardynał pastor
ryby: karp śledź łosoś dorsz okoń sandacz szczupak płotka
napoje_mleczne: jogurt kefir maślanka
czynności_sportowe: bieganie skakanie pływanie maszerowanie marsz trucht
ubranie:  garnitur smoking frak żakiet marynarka koszula bluzka sweter sweterek sukienka kamizelka spódnica spodnie
mebel: krzesło fotel kanapa łóżko wersalka sofa stół stolik ława
przestępca: morderca zabójca gwałciciel złodziej bandyta kieszonkowiec łajdak łobuz
mięso_wędliny wieprzowina wołowina baranina cielęcina boczek baleron kiełbasa szynka schab karkówka dziczyzna
drzewo: dąb klon wiąz jesion świerk sosna modrzew platan buk cis jawor jarzębina akacja
źródło_światła: lampa latarka lampka żyrandol żarówka reflektor latarnia lampka
organ: wątroba płuco serce trzustka żołądek nerka macica jajowód nasieniowód prostata śledziona
oddziały: kompania pluton batalion brygada armia dywizja pułk
napój_alkoholowy: piwo wino wódka dżin nalewka bimber wiśniówka cydr koniak wiśniówka
kot_drapieżny: puma pantera lampart tygrys lew ryś żbik gepard jaguar
metal: żelazo złoto srebro miedź nikiel cyna cynk potas platyna chrom glin aluminium
samolot: samolot odrzutowiec awionetka bombowiec myśliwiec samolocik helikopter śmigłowiec
owoc: jabłko gruszka śliwka brzoskwinia cytryna pomarańcza grejpfrut porzeczka nektaryna
pościel: poduszka prześcieradło kołdra kołderka poduszeczka pierzyna koc kocyk pled
agd: lodówka kuchenka pralka zmywarka mikser sokowirówka piec piecyk piekarnik
'''

vectors = {}

def best(w, K):
    v = vectors[w]
    
    L = sorted([ (v.dot(vectors[w]), w) for w in vectors])
    L.reverse()
    
    return L[:K]


name = 'word_embedings_file.txt'

for x in open(name):
    L = x.split()
    if len(L) < 2:
        continue
    w = L[0]
    values = [float(x) for x in L[1:]]
    v = np.array(values)
    length = v.dot(v) ** 0.5
    vectors[w] = v / length
    
C = {}

def choose_another(A, a):
    while True:
        b = random.choice(A)
        if a != b: 
            return b

words = set()
    
for x in clusters_txt.split('\n'):
    L = x.split()
    if len(L) < 2:
        continue    
    C[L[0]] = L[1:]
    words.update(L[1:])
    
groups = list(C.keys())
    
score = 0.0
N = 30000    
N = 500000

bad = all_words = 0.0

for w in words:
    if not w in vectors:
        print (w, end=' ')
        bad += 1
    all_words += 1
    
print ('PROBLEMS:', bad / all_words)

print ("Start")
for i in range(N):
    g1 = random.choice(groups)
    A = C[g1]
    B = C[choose_another(groups, g1)]
    
    a1 = random.choice(A)
    a2 = choose_another(A, a1)
    b = random.choice(B)
    
    #print (a1,a2,b)
    if not a1 in vectors or not a2 in vectors or not b in vectors:
        score += 0.5
        continue
    
    va1 = vectors[a1]
    va2 = vectors[a2]
    vb  = vectors[b]    
    
    if va1.dot(va2) > va1.dot(vb):
        score += 1.0
    else:
        pass
        #print (a1,a2,'--',b)    
        
print ('TOTAL SCORE:', score/N) 
            
     

