## 1.
```bash
sudo ip link set enp0s3 name enp0
sudo ip addr add 192.168.1.1/24 dev enp0
sudo ip link set enp0 up
sudo ip route add default via 192.168.1.2
```

## 2.
```bash
sudo ip link set enp0s3 name enp0
sudo ip addr add 192.168.1.2/24 dev enp0
sudo ip link set enp0 up
sudo ip route add default via 192.168.1.3
```

## 3.
```bash
sudo ip link set enp0s3 name enp0
sudo ip link set enp0s8 name enp1
sudo ip addr add 192.168.1.3/24 dev enp0
sudo ip addr add 192.168.2.1/24 dev enp1
sudo ip link set enp0 up
sudo ip link set enp1 up
```

## 4.
```bash
sudo ip link set enp0s3 name enp-out
sudo ip addr add 192.168.2.2/24 dev enp-out
sudo ip link set enp-out up
sudo ip route add default via 192.168.2.1
```

