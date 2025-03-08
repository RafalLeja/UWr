## PREPARATION

```bash
# V1
sudo ip link set enp0s3 name enp-rem
sudo ip link set enp0s8 name enp-loc
sudo ip link set up enp-rem
sudo ip addr add 172.16.0.1/16 dev enp-rem

# V2
sudo ip link set enp0s3 name enp-rem
sudo ip link set enp0s8 name enp-loc
sudo ip link set up enp-rem
sudo ip addr add 172.16.0.2/16 dev enp-rem
```

## Skonfiguruj maszyny Virbian3 i Virbian4, które będą miały po jednej karcie sieciowej połączonej odpowiednio z siecią local1 i local2. Po ich uruchomieniu zmień nazwę wirtualnej karty sieciowej w tych maszynach na enp-loc. Dzięki temu osiągniesz konfigurację jak na poniższym rysunku.

```bash
# V3
sudo ip link set enp0s3 name enp-loc

# V4
sudo ip link set enp0s3 name enp-loc
```

## Na wszystkich maszynach sprawdź wynik polecenia sysctl net.ipv4.ip forward i jeśli zwracaną wartością jest 0, wykonaj polecenie

```bash
sysctl net.ipv4.ip_forward

sysctl net.ipv4.ip_forward=1
```

## Aktywuj interfejsy enp-loc na maszynach Virbian1 i Virbian3 i przypisz im adresy IP równe odpowiednio 192.168.11.1/24 i 192.168.11.2/24. Aktywuj interfejsy enp-loc na maszynach Virbian2 i Virbian4 i przypisz im adresy IP równe odpowiednio 192.168.12.1/24 i 192.168.12.2/24. Uzyskana konfiguracja wygląda teraz jak na poniższym rysunku

```bash
# V3
sudo ip link set up enp-loc
sudo ip addr add 192.168.11.2/24 dev enp-loc

# V1
sudo ip link set up enp-loc
sudo ip addr add 192.168.11.1/24 dev enp-loc

# V4
sudo ip link set up enp-loc
sudo ip addr add 192.168.12.2/24 dev enp-loc

# V2
sudo ip link set up enp-loc
sudo ip addr add 192.168.12.1/24 dev enp-loc
```

## Na każdej maszynie poleceniem ping sprawdź osiągalność najbliższych interfejsów najbliżej położonych maszyn.

```bash
# V1
ping 172.16.0.2
ping 192.168.11.2

# V2
ping 172.16.0.1
ping 192.168.12.2

# V3
ping 192.168.11.1

# V4
ping 192.168.12.1
```

## Z maszyny Virbian1 sprawdź osiągalność interfejsu enp-loc maszyny Virbian2

```bash
# V1
ping 192.168.12.1

# V2
ping 192.168.11.1
```

## Spróbujmy to naprawić dodając na maszynach Virbian1 i Virbian2 odpowiednie wpisy w ich tablicach routingu. 

```bash
# V1
sudo ip route add 192.168.12.0/24 via 172.16.0.2

# V2
sudo ip route add 192.168.11.0/24 via 172.16.0.1

ip route
```

## Z maszyny Virbian1 sprawdź osiągalność interfejsu enp-loc maszyny Virbian4 wydając na niej polecenie ping 192.168.12.2

```bash
# V1
ping 192.168.12.2
```

## Spróbujmy naprawić sytuację dodając na maszynie Virbian4 informację pozwalającą trafić do pozostałych dwóch sieci

```bash
# V4
sudo ip route add default via 192.168.12.1

# V3
sudo ip route add default via 192.168.11.1

ip route

# V1
ping 172.16.0.2
ping 192.168.11.2
ping 192.168.12.2

# V2
ping 172.16.0.1
ping 192.168.11.2
ping 192.168.12.2

# V3
ping 172.16.0.1
ping 172.16.0.2
ping 192.168.12.2

# V4
ping 172.16.0.1
ping 172.16.0.2
ping 192.168.11.2

```

## Wyświetl trasę z maszyny Virbian3 do maszyny Virbian4 poleceniem traceroute

```bash
# V3
traceroute 192.168.12.2

# V4
traceroute 192.168.11.2
```

## deconf

```bash
# V1
sudo ip addr flush dev enp-rem
sudo ip addr flush dev enp-loc
sudo ip link set down enp-rem
sudo ip link set down enp-loc

# V2
sudo ip addr flush dev enp-rem
sudo ip addr flush dev enp-loc
sudo ip link set down enp-rem
sudo ip link set down enp-loc

# V3
sudo ip addr flush dev enp-loc
sudo ip link set down enp-loc

# V4
sudo ip addr flush dev enp-loc
sudo ip link set down enp-loc
```
