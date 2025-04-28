## 1
```bash
sudo ip link set enp0s3 name enp0
sudo ip addr add 192.168.0.1/24 dev enp0
sudo ip link set enp0 up
```

## 2
```bash
sudo ip link set enp0s3 name enp0
sudo ip addr add 192.168.0.2/24 dev enp0
sudo ip link set enp0 up
```

## 1
```bash
ping 192.168.0.2

ping -b 192.168.0.255

ip neigh

sudo ip neigh flush all
```

## 2
```bash
ip neigh

sudo ip neigh flush all
```
