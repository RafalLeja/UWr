#!/bin/bash



cleanup() {
    printf "\n"
    exit 0
}

trap cleanup EXIT INT TERM

( read -rsn1; kill -s INT $$ ) &

while true; do
    values=$(grep "cpu " /proc/stat)
    sum=$(grep "cpu " /proc/stat | awk '{sum=0; for(i=2; i<=NF; i++) sum+=$i; print sum}')
    user=$(echo $values | awk -v s="$sum" '{user=$2; printf "%.1f", user/s*100}')
    system=$(echo $values | awk -v s="$sum" '{sys=$4; printf "%.1f", sys/s*100}')
    idle=$(echo $values | awk -v s="$sum" '{idle=$5; printf "%.1f", idle/s*100}')
    iowait=$(echo $values | awk -v s="$sum" '{iowait=$6; printf "%.1f", iowait/s*100}')
    printf "CPU: %s%% user, %s%% system, %s%% idle, %s%% iowait\r" $user $system $idle $iowait
    sleep 1
done