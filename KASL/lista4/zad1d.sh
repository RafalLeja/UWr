#!/bin/bash

echo "looking for mp3 files in $1"

mapfile -t mp3_files < <(find "$1" -type f -iname "*.mp3")

mapfile -t mp3_info < <(for file in "${mp3_files[@]}"; do 
    mp3info -p "%l (%a): %t\n" "$file"
done)

file_count=${#mp3_files[@]}
if [ $file_count -eq 0 ]; then
    echo "No mp3 files found"
    exit 1
fi

options=()
for i in "${!mp3_info[@]}"; do
    options+=("$i" "${mp3_info[$i]}")
done

while true; do
    choice=$(yad --list --title "Wybierz utwór" --column="nr" --column="piosenka" --print-column="1" "${options[@]}" | tr -d '|')

    echo "choice: $choice"
    if [ $choice ]; then
        echo "Playing ${mp3_info[$choice]}"
        mplayer "${mp3_files[$choice]}"
    else
        echo "No selection made"
        exit 1
    fi
done
