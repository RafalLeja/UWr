### Co przechowuje ten rejestr? 

- Rejestr sterujący CR3 w procesorach x86-64 przechowuje bazowy adres tablicy stron (Page Table Directory) używanej do translacji adresów wirtualnych na fizyczne. Tablica stron jest używana przez mechanizm translacji pamięci, który przekształca adresy wirtualne używane przez programy w adresy fizyczne w pamięci RAM.

### Czemu jest on dostępny wyłącznie dla programów działających w trybie uprzywilejowanym (ang. supervisor mode)?

 - Rejestr CR3 jest dostępny wyłącznie dla programów działających w trybie uprzywilejowanym, znanej również jako tryb jądra (kernel mode) lub tryb systemowy. Istnieje kilka powodów, dla których ten rejestr jest ograniczony tylko do programów uprzywilejowanych:

    1. Bezpieczeństwo: Dostęp do CR3 umożliwia kontrolę nad translacją adresów pamięci, co może wpływać na działanie innych programów lub systemu operacyjnego. Ograniczenie dostępu do CR3 do programów uprzywilejowanych pomaga zapobiegać nieuprawnionym zmianom w mechanizmach translacji adresów i utrzymaniu integralności systemu.

    2. Ochrona pamięci: Dostęp do CR3 umożliwia manipulację tablicą stron, co może prowadzić do błędnej translacji adresów lub dostępu do nieautoryzowanej pamięci. Ograniczenie dostępu do CR3 dla programów użytkownika chroni przed możliwością naruszenia izolacji pamięci między różnymi procesami, co jest kluczowe dla zapewnienia bezpieczeństwa i stabilności systemu.

###  Czy moglibyśmy zagwarantować izolację, jeśli pamięć przechowująca tablicę stron była dostępna w trybie użytkownika?

 - Gwarantowanie izolacji byłoby trudne, gdyby pamięć przechowująca tablicę stron była dostępna w trybie użytkownika. Jeśli użytkownik miałby bezpośredni dostęp do tablicy stron, mógłby modyfikować jej zawartość i zmieniać translację adresów, co prowadziłoby do błędów w działaniu systemu lub nawet do naruszenia bezpieczeństwa. Ograniczenie dostępu do tablicy stron dla programów użytkownika jest kluczowym elementem w architekturze ochrony pamięci i izolacji procesów, które są niezbędne dla bezpiecznego i niezawodnego działania systemu operacyjnego.