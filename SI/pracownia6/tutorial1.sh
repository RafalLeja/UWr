#/bin/bash
IpAddr=$1

(end=$((SECONDS+2)); while [ $SECONDS -lt $end ]; do netstat -tan | grep $IpAddr ; done) > tcp_log &

wget http://$IpAddr/ 
