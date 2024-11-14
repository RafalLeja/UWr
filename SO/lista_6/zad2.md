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
bit set-gid oznacza że wszystkie pliki utworzone w katalogu dziedziczą grupę właściciela katalogu

bit sticky ogranicza możliwość usuwania plików z katalogu do właściciela pliku, właściciela katalogu i roota

### Napisz w pseudokodzie i zreferuj procedurę «bool my_access(struct stat *sb, int mode)». Pierwszy i drugi argument opisano odpowiednio w stat(2) i access(2). Dla procesu o tożsamości zadanej przez getuid(2) i getgroups(2) procedura «my_access» sprawdza czy proces ma upoważniony dostęp «mode» do pliku o metadanych wczytanych do «sb».
```C
struct stat {
    dev_t      st_dev;      /* ID of device containing file */
    ino_t      st_ino;      /* Inode number */
    mode_t     st_mode;     /* File type and mode */
    nlink_t    st_nlink;    /* Number of hard links */
    uid_t      st_uid;      /* User ID of owner */
    gid_t      st_gid;      /* Group ID of owner */
    dev_t      st_rdev;     /* Device ID (if special file) */
    off_t      st_size;     /* Total size, in bytes */
    blksize_t  st_blksize;  /* Block size for filesystem I/O */
    blkcnt_t   st_blocks;   /* Number of 512 B blocks allocated */

    /* Since POSIX.1-2008, this structure supports nanosecond
        precision for the following timestamp fields.
        For the details before POSIX.1-2008, see VERSIONS. */

    struct timespec  st_atim;  /* Time of last access */
    struct timespec  st_mtim;  /* Time of last modification */
    struct timespec  st_ctim;  /* Time of last status change */

#define st_atime  st_atim.tv_sec  /* Backward compatibility */
#define st_mtime  st_mtim.tv_sec
#define st_ctime  st_ctim.tv_sec
};
```

```C
bool my_access(struct stat *sb, int mode) {
    // Pobierz ID użytkownika procesu i jego grupy
    if(geteuid() == 0) return true;
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