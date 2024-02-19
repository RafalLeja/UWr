Feature: Realizacja zamówienia w sklepie internetowym

    Scenario: Wybór i zakup produktów przez klienta
    		Given: Klient jest zalogowany do swojego konta w sklepie internetowym
    		When: Klient wybiera produkty i dodaje je do koszyka
    		And: Klient przechodzi do koszyka i wybiera formę dostawy oraz płatności
    		And: Klient podaje niezbędne dane, takie jak adres dostawy i dane karty płatniczej
    		And: Klient potwierdza zamówienie
    		Then: Klient otrzymuje potwierdzenie z numerem zamówienia
        And: Klient śledzi status zamówienia, otrzymując powiadomienia o postępie realizacji
        And: Klient odbiera dostarczone produkty
        And: Klient ocenia jakość obsługi i zakupionych produktów

    Scenario: Obsługa wyjątków
        Given: Produkt nie jest dostępny
        When: Klient otrzymuje informację o niedostępności produktu
        Then: Klient podejmuje odpowiednie działania

        Given: Problem z płatnością
        When: Klient otrzymuje komunikat o błędzie płatności
        Then: Klient podejmuje odpowiednie działania
