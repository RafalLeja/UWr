### Jaką rolę pełnią bity uprawnień «rwx» dla katalogów w systemach uniksowych?

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
bit set-gid oznacza że jeśli uruchamiamy plik z takim bitem to proces dziedziczy grupę pliku, a nie grupę procesu

bit sticky ogranicza możliwość usuwania plików z katalogu do właściciela pliku, właściciela katalogu i roota

### Napisz w pseudokodzie i zreferuj procedurę «bool my_access(struct stat *sb, int mode)». Pierwszy i drugi argument opisano odpowiednio w stat(2) i access(2). Dla procesu o tożsamości zadanej przez getuid(2) i getgroups(2) procedura «my_access» sprawdza czy proces ma upoważniony dostęp «mode» do pliku o metadanych wczytanych do «sb».

```C
bool my_access(struct stat *sb, int mode) {
    // Pobierz ID użytkownika procesu i jego grupy
    int user_id = getuid();
    int group_id = getgid();
    int *groups;
    int num_groups = getgroups(0, NULL);  // Liczba grup użytkownika
    groups = malloc(num_groups * sizeof(int));
    getgroups(num_groups, groups);        // Pobierz grupy użytkownika

    // Sprawdzenie uprawnień właściciela
    if (sb->st_uid == user_id) {
        if ((mode & R_OK) && !(sb->st_mode & S_IRUSR)) return false;
        if ((mode & W_OK) && !(sb->st_mode & S_IWUSR)) return false;
        if ((mode & X_OK) && !(sb->st_mode & S_IXUSR)) return false;
    }
    // Sprawdzenie uprawnień grupy
    else if (sb->st_gid == group_id || is_in_groups(groups, num_groups, sb->st_gid)) {
        if ((mode & R_OK) && !(sb->st_mode & S_IRGRP)) return false;
        if ((mode & W_OK) && !(sb->st_mode & S_IWGRP)) return false;
        if ((mode & X_OK) && !(sb->st_mode & S_IXGRP)) return false;
    }
    // Sprawdzenie uprawnień innych
    else {
        if ((mode & R_OK) && !(sb->st_mode & S_IROTH)) return false;
        if ((mode & W_OK) && !(sb->st_mode & S_IWOTH)) return false;
        if ((mode & X_OK) && !(sb->st_mode & S_IXOTH)) return false;
    }

    free(groups);
    return true;
}

// Funkcja pomocnicza sprawdzająca, czy gid znajduje się na liście grup użytkownika
bool is_in_groups(int *groups, int num_groups, int gid) {
    for (int i = 0; i < num_groups; i++) {
        if (groups[i] == gid) return true;
    }
    return false;
}
```