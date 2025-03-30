## 1
```
sudo ip link set enp0s3 name enp-rem4
sudo ip link set enp0s8 name enp-rem1
sudo ip addr add dev enp-rem1 192.168.1.1/24
sudo ip link set enp-rem1 up
sudo ip route add default via 192.168.1.2
```

## 2
```
sudo ip link set enp0s3 name enp-rem1
sudo ip link set enp0s8 name enp-rem2
sudo ip addr add dev enp-rem1 192.168.1.2/24
sudo ip link set enp-rem1 up
sudo ip addr add dev enp-rem2 192.168.2.2/24
sudo ip link set enp-rem2 up
```

## 3
```
sudo ip link set enp0s3 name enp-rem2
sudo ip link set enp0s8 name enp-rem3
sudo ip addr add dev enp-rem2 192.168.2.3/24
sudo ip link set enp-rem2 up
sudo ip addr add dev enp-rem3 192.168.3.3/24
sudo ip link set enp-rem3 up
```

## 4
```
sudo ip link set enp0s3 name enp-rem3
sudo ip link set enp0s8 name enp-rem4
sudo ip addr add dev enp-rem3 192.168.3.4/24
sudo ip link set enp-rem3 up
sudo ip route add default via 192.168.3.3
```



