1. Do wyboru zbioru pamięci podręcznej używamy bitów znajdujących się w środku adresu, zaraz przed
offsetem bloku. Czemu jest to lepszy pomysł niż używanie najbardziej znaczących bitów adresu?

        Zwiększa to trafność pamięci ponieważ możemy przechować więcej bloków które są obok siebie

2. Zdecydowana większość procesorów posiada odrębną pamięć podręczną pierwszego poziomu dla danych
i dla instrukcji. Jakie korzyści to przynosi?

        Pamięć instrukcji jest read-only co upraszcza budowe. Procesor może wczytywać jednocześnie instrukcje oraz dane w jednym cyklu

3. Które fragmenty pamięci system operacyjny musi skonfigurować w trybie dostępu write-through?

        pamięcią główną