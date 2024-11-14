### Na podstawie §38.2 i §38.3 wyjaśnij czemu programy uprzywilejowane należy projektować w taki sposób, by operowały z najmniejszym możliwym zestawem upoważnień (ang. the least privilege).
gdy nasz program działa z najmniejszym możliwym zestawem upoważnień, to w przypadku ataku na nasz program, atakujący nie będzie mógł wykonać wielu działań, które by mógł wykonać gdyby nasz program działał z pełnymi uprawnieniami. W ten sposób ograniczamy możliwość ataku na nasz program.

### Zreferuj wytyczne dotyczące projektowania takich programów.
- utrzymuj uprawnienia jak najkrócej
- zrzuć uprawnienia permamentnie, jeśli nie będą potrzebne
- zrzuć uprawnienia przed execve
- nie uruchamiaj shella z uprawnieniami
- zamknij pliki przed execve

### Zapoznaj się z §39.1 i wytłumacz czemu standardowy zestaw funkcji systemu uniksowego do implementacji programów uprzywilejowanych jest niewystarczający.
standardowy zestaw funkcji jest skoplikowany,
ma różne działanie dla uprzywilejowanych i nieuprzywilejowanych procesów
oraz różne działanie dla różnych systemów uniksowych

### Jak starają się to naprawić zdolności (ang. capabilities)?
Zdolności pozwalają na bardziej precyzyjne zarządzanie uprawnieniami procesów, dzięki czemu procesy mogą wykonywać tylko te operacje, które są im potrzebne.

### Dla nieuprzywilejowanego procesu posiadającego zdolności «CAP_DAC_READ_SEARCH» i «CAP_KILL» jądro pomija sprawdzanie upoważnień do wykonywania pewnych akcji – wymień je.
CAP_DAC_READ_SEARCH
    * Bypass file read permission checks and directory read and execute permission checks;
    * invoke open_by_handle_at(2);
    * use the linkat(2) AT_EMPTY_PATH flag to create a link to a file referred to by a file descriptor.

CAP_KILL
    Bypass permission checks for sending signals (see kill(2)).  This includes use of the ioctl(2) KDSIGAC‐
    CEPT operation.

### Kiedy proces użytkownika może wysłać sygnał do innego procesu?
For  a  process  to  have  permission  to  send  a signal, it must either be privileged (under Linux: have the
CAP_KILL capability in the user namespace of the target process), or the real or  effective  user  ID  of  the
sending  process  must  equal the real or saved set-user-ID of the target process.  In the case of SIGCONT, it
suffices when the sending and receiving processes belong to the same session.  (Historically, the  rules  were
different; see NOTES.)
-- man 2 kill