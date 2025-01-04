#!/bin/bash

# Funkcja naprawiająca podany tekst
fix_text() {
    local input_text="$1"

    # Poprawianie błędów w tekście
    fixed_text=$(echo "$input_text" |
        sed 's/»/ż/g' |
        sed 's/«/ś/g' |
        sed 's/¡/ą/g' |
        sed 's/¦/ę/g' |
        sed 's//fi/g' |
        sed 's/¢/ć/g' |
        sed 's/ª/ł/g' |
        sed 's/¬/ń/g' |
        sed 's/±/ó/g' |
        sed 's/¥/ź/g' |
        sed 's/¥/ź/g' |
        sed 's/¹/ź/g' |
        sed 's//"/g' |
        sed 's//"/g' |
        sed 's//"/g' |
        sed 's///g')

    echo "$fixed_text"
}

# Sprawdzenie, czy podano argument
if [ "$#" -ne 1 ]; then
    echo "Użycie: $0 nazwa_pliku"
    exit 1
fi

# Pobranie nazwy pliku
file_name="$1"

# Sprawdzenie, czy plik istnieje
if [ ! -f "$file_name" ]; then
    echo "Plik $file_name nie istnieje."
    exit 1
fi

# Odczytanie zawartości pliku
input_text=$(cat "$file_name")

# Wywołanie funkcji
fixed_text=$(fix_text "$input_text")

# Wyświetlenie poprawionego tekstu
echo "$fixed_text"