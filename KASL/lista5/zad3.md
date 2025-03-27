# pliki

## /etc/hostname
- nazwa systemowa komputera

## /etc/machine-id
- unikalny identyfikator maszyny

## /etc/os-release
- informacje o systemie

# polecenia

## hostname
- nazwa systemowa komputera
- zapisana w pliku /etc/hostname (domyslnie)
- ustawiana przez polecenie hostname

## hostnameclt
- polecenie do zarzadzania nazwa systemowa komputera
- ustawia/wypisuje:
  - nazwe systemowa komputera
  - icon-name
  - chassis
  - deployment
  - location

## uuid
- generuje unikalny identyfikator
- wyświetla indormacje o UUID
- standard ISO/IEC 11578:1996

## uuidgen
- generuje unikalny identyfikator

## dbus-uuidgen
- generuje unikalny identyfikator systemu
- zapisuje do pliku /etc/machine-id
- sprawdza czy identyfikator jest zgodny

## uname
- wyświetla informacje o systemie

## lsb_release
- wyświetla informacje o systemie
- czyta z pliku /etc/os-release