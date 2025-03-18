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
    choice=$(whiptail --title "Wybierz utwór" --menu "Lista utworów" 20 60 10 "${options[@]}" 3>&1 1>&2 2>&3)

    if [ $? -eq 0 ]; then
        echo "Playing ${mp3_info[$choice]}"
        mplayer "${mp3_files[$choice]}"
    else
        echo "No selection made"
        exit 1
    fi
done

# PS3="Wybierz utwór: "
# while true; do
#     select SONG in "${mp3_info[@]}"; do
#         if [[ -z "$REPLY" ]]; then
#             echo "Zakończono"
#             exit 0
#         fi
#         if [[ "$REPLY" =~ [A-Za-z] ]] || [[ "$REPLY" -gt "$file_count" ]] || [[ "$REPLY" -lt 1 ]]; 
#         then
#             echo "Zła opcja"
#             continue
#         else
#             echo "Playing $SONG"
#             mplayer "${mp3_files[$REPLY]}"
#         fi
#         break
#     done

#     if [[ $? -ne 0 ]]; then
#         echo "Miłego dnia!"
#         exit 1
#     fi
# done
