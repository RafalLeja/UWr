### Jaką rolę pełnią bity uprawnień «rwx» dla katalogów w systemach uniksowych?

- r - pozwala na odczyt zawartości katalogu
- w - pozwala na zapis do katalogu
- x - przeszukiwanie katalogu
- X - przeszukiwanie katalogu jeśli jest ono wymagane

```shell

ls -al

total 12
drwxr-xr-x 2 rafal rafal 4096 Nov 12 20:53 .
drwxr-xr-x 9 rafal rafal 4096 Nov 12 20:04 ..
-rw-r--r-- 1 rafal rafal  901 Nov 12 20:53 zad1.md
-rw-r--r-- 1 rafal rafal    0 Nov 12 20:53 zad2.md
  ^  ^  ^
  |  |  |
  |  |  +-- uprawnienia innych
  |  +-- uprawnienia grupy
  +-- uprawnienia właściciela

ls -l /bin/passwd

-rwsr-xr-x 1 root root 59976 Feb  6  2024 /bin/passwd
   ^
   |
   +-- bit setuid

stat tmp

  File: /tmp
  Size: 4096            Blocks: 8          IO Block: 4096   directory
Device: 820h/2080d      Inode: 57346       Links: 11
Access: (1777/drwxrwxrwt)  Uid: (    0/    root)   Gid: (    0/    root)
                       ^
                       |
                       +-- bit sticky
```


### Opisz znaczenie bitów «set-gid» i «sticky» dla katalogów.
bit set-gid oznacza że wszystkie pliki utworzone w katalogu dziedziczą grupę właściciela katalogu

bit sticky ogranicza możliwość usuwania plików z katalogu do właściciela pliku, właściciela katalogu i roota

