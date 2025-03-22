addr=$1

standard=$(sudo traceroute -I -n $addr | tail -n +2 | awk '{if (NF>=5) print $1, $2, ($3+$5+$7)/3 " ms"; else print $0}')

custom=$(sudo ./traceroute $addr)

echo "$standard"

echo "$custom"
