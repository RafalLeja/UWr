## 0.
```bash
sudo ip link set enp0s3 name enp-ext
sudo ip link set enp0s8 name enp-add1
sudo ip link set enp0s9 name enp-loc1

sudo ip addr add dev enp-loc1 172.18.0.1/16
sudo ip link set enp-loc1 up
sudo ip addr add dev enp-add1 192.168.0.1/24
sudo ip link set enp-add1 up
sudo dhclient -v enp-ext

ext=$(ip a show enp-ext | grep "inet " | awk '{print $2}' | awk -F/ '{print $1}')
echo $ext
```

## 1.
```bash
sudo ip link set enp0s3 name enp-loc1
sudo ip addr add dev enp-loc1 172.18.0.2/16
sudo ip link set enp-loc1 up
```

## 2.
```bash
sudo ip link set enp0s3 name enp-add1
sudo ip addr add dev enp-add1 192.168.0.2/24
sudo ip link set enp-add1 up
```

## 1.
```bash
sudo ip route add default via 172.18.0.1
```

## 2.
```bash
sudo ip route add default via 192.168.0.1
```

## 0.
```bash
sudo nft add table ip my_table
sudo nft add chain ip my_table my_rules {type nat hook postrouting priority srcnat\; }
sudo nft add rule my_table my_rules ip saddr 172.18.0.0/16 snat to $ext
```