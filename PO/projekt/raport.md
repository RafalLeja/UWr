# Raport projektu z programowania obiektowego

### Rafał Leja 340879 20.06.2023

Implementacja gry 2048 w Ruby zakończyła się pozywtywnie. Gra dodatkowo posiada dodawanie nazwy gracza, zliczanie punktów oraz zapisywanie najlepszych wyników do pliku. Programowanie obiektowe pozwoliło uprościć cały projekt, do paru konkretnych elementów,
które można wykorzystywać wielokrotnie, bez konieczności pisania ich od nowa. Biblioteka ruby2d pozwoliła na zaprogramowanie interfejsu graficznego, który dorównuje innym programom używających interfejsów graficznych.

Ostatecznie zaimplementowałem 7 klas:
- SceneManager
- Scene
- InputField
- Grid
- Block
- ScoreCounter
- Leaderboard
  
Każda klasa jest odpowiedzialna za inne elementy gry, co ułatwie czytanie i zrozumienie kodu gry.

Lista klas rózni się od tej pierwotnie założonej, ponieważ wielu rzeczy i problemów nie dało się przewidzieć, bez wcześniejszej wiedzy na temat biblioteki ruby2d czy samej gry. 

Podczas pisania tego projektu, dowiedziałem się, jak lepiej projektować programy, jak używać biblioteki ruby2d, dlaczego programowanie obiektowa jest używane do większych projektów oraz jak sporządzić dokumentacje.

Do zrobienia komentarzy użyłem wtyczki mintlify, która używa sztucznej inteligencji do zrozumienia i opisania kodu. W niektórych miejscach potrzebna była interwencja człowieka, ponieważ komentarze nie zawsze były czytelne i zrozumiałe.

Do zrobienia dokumentacji chciałem użyć programów do generowania dokumentacji w ruby - rdoc oraz yard. Niestety nie udało mi się wygenerować satysfakcjonującej dokumentacji, być możę że komentarze nie pasowały do składni rdoc i yard. Ostatecznie dokumentacje napisałem ręcznie.