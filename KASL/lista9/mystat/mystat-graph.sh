#!/bin/bash

LOGFILE="/var/log/mystat.log"
OUTDIR="/var/lib/mystat"
DATAFILE=$(mktemp)

# Wydobądź dane z ostatnich 24h (zakładamy logowanie co minutę = 1440 linii)
grep "AVG" "$LOGFILE" | tail -n 1440 | awk -F'[][]|AVG: |%| ' '{
    timestamp=$3;
    avg=$6;
    printf "%s %s\n", timestamp, avg
}' > "$DATAFILE"

# Wygeneruj wykres PNG za pomocą gnuplot
gnuplot <<EOF
set terminal png size 1024,600
set output "$OUTDIR/cpu_usage_24h.png"
set xdata time
set timefmt "%H:%M:%S"
set format x "%H:%M"
set xlabel "Czas"
set ylabel "Obciążenie CPU (%)"
set title "Średnie obciążenie CPU z ostatnich 24h"
set grid
set yrange [0:*]
plot "$DATAFILE" using 1:2 with lines title "AVG (%)" lw 2 lc rgb "blue"
EOF

# Sprzątanie
rm "$DATAFILE"
