### Korzystając z poleceń «stat» i «ls -lia» zaprezentuj jak jądro systemu operacyjnego trawersuje ścieżkę bezwzględną «/usr/bin/cc». Od jakiego numeru i-węzła algorytm zaczyna działanie?

ścieżka bezwzględna zaczyna się od folderu głównego `/` (inode 2) i przechodzimy do `/usr` (inode 65537), `/usr/bin` (inode 1241) i na końcu `/usr/bin/cc` (inode 40719) który jest linkiem do `/etc/alternatives/cc`. 

### Skąd sterownik uniksowego systemu plików wie gdzie na dysku znajduje się i-ty bajt pliku?
zakładając że blok ma rozmiar 4096 bajtów, to i-ty bajt pliku znajduje się w bloku o numerze `(i / 4096) + 1` i wewnątrz tego bloku na pozycji `i % 4096` dla i < 4096 * 12.
13 wskazuje na blok pośredni, 14 na blok podwójnie pośredni, 15 na blok potrójnie pośredni.

### Próba utworzenia dowiązania do pliku «/proc/version» kończy się błędem «EXDEV». Czemu nie możemy tworzyć dowiązań do plików znajdujących się w obrębie innych zamontowanych systemów plików?

Dowiązanie zawiera numer i-node pilku

skoro w dwóch róznych systemach plików mogą być dwa pliki o tym samym numerze i-node, to dowiązanie wskazujące na numer i-node pliku w innym systemie plików nie miałoby sensu.