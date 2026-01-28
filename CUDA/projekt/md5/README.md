Projekt kompiluje się za pomocą Makefile'a. Aby skompilować projekt, należy użyć polecenia:

```bash
make
```

W folderze ./bin/ pojawi się plik wykonywalny o nazwie `app`

aby wyświetlić opcje programu wystarczy użyć polecenia:

```bash
./bin/app --help
```

aby łamać hasło z cyfr oraz małych liter o długości mniejszej równej 7 można użyć polecenia:

```bash
./bin/app -p -i <plik z hashem> -m 7 -nl
```

W folderze ./benchmark/  znajduje się skrypt w pythonie do generowania wykresów

Aby stworzyć plik z hashem hasła można użyć polecenia:

```bash
echo -n "twoje_haslo" | md5sum > plik.txt
```
