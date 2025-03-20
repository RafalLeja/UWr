#!/bin/bash

# Loop through all files matching the pattern zad1*.sh
for file in zad1*.sh; do
    # Construct the new filename by replacing zad1 with zad2
    new_file="${file/zad1/zad2}"
    
    # Rename the file
    mv "$file" "$new_file"
    echo "Renamed: $file -> $new_file"
done
