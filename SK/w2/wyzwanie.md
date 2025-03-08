## Uruchom maszyny i nazwij ich interfejsy tak jak na rysunku powyżej. Uzyskaj konfigurację sieciową dla interfejsu enp-ext maszyny Virbian0 poleceniem

```bash
# V0
sudo ip link set enp0s3 name enp-ext
sudo ip link set enp0s8 name enp-loc0
sudo dhclient -v enp-ext
sudo ip link set up enp-loc0
sudo ip addr add 192.168.0.1/24 dev enp-loc0
ip addr

ping 192.168.0.2

# V1
sudo ip link set enp0s3 name enp-loc0
sudo ip link set enp0s8 name enp-loc1
sudo ip link set up enp-loc0
sudo ip link set up enp-loc1
sudo ip addr add 192.168.0.2/24 dev enp-loc0
sudo ip addr add 192.168.1.1/24 dev enp-loc1
ip addr

ping 192.168.0.1
ping 192.168.1.2

# V2
sudo ip link set enp0s3 name enp-loc1
sudo ip link set up enp-loc1
sudo ip addr add 192.168.1.2/24 dev enp-loc1
ip addr

ping 192.168.1.1
```

## Skonfiguruj routing:

```bash
# V0
sudo ip route add 192.168.1.0/24 via 192.168.0.2

# V1
sudo ip route add default via 192.168.0.1

# V2
sudo ip route add default via 192.168.1.1
```

## Z każdej maszyny wirtualnej powinny być teraz osiągalne wszystkie interfejsy

```bash
# V0
ping 192.168.1.1
ping 192.168.1.2

# V2
ping 192.168.0.2
ping 192.168.0.1

traceroute 192.168.0.1
```
## Z maszyny Virbian0 pingnij adres 8.8.8.8

```bash
# V0
ping 8.8.8.8

# V2
ping 8.8.8.8
traceroute 8.8.8.8
```

Należy poinformować router podłączony do V0 o trasie do sieci