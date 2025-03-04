- Utwórz dodatkową maszynę wirtualną Virbian2. Podłącz karty sieciowe Adapter1 maszyn
Virbian1 i Virbian2 do wirtualnej sieci local1 i następnie uruchom obie maszyny

- Aktywuj karty sieciowe w obu urządzeniach poleceniem ip i sprawdź stan warstwy fizycznej kart poleceniem ethtool.

```bash

# 0
sudo ip link set up dev enp0s3
sudo ip addr add 192.168.100.1/24 dev enp0s3

# 1
sudo ip link set up dev enp0s3
sudo ip addr add 192.168.100.2/24 dev enp0s3
```

- Poleceniem ping sprawdź, czy jedna maszyna jest osiągalna z drugiej. Jaki jest RTT?
Obejrzyj przesyłane pakiety Wiresharkiem. Wskaż w pakiecie miejsce w którym przechowywany jest źródłowy i docelowy adres IP.

```bash
# 0
ping 192.168.100.2
```

- Wykorzystaj program iperf3, żeby zbadać przepustowość połączenia między maszynami.

```bash
# 0
iperf3 -c 192.168.100.2

# 1
iperf3 -s
```

- Z maszyny Virbian1 połącz się z serwerem echa maszyny Virbian2. Zaobserwuj przesyłane
pakiety w Wiresharkach uruchomionych jednocześnie na obu maszynach.

```bash
# 0
telnet 192.168.100.2 7
```

- Zdekonfiguruj karty sieciowe obu maszyn i wyłącz wirtualne maszyny.

```bash
# 0
sudo ip addr flush dev enp0s3
sudo ip link set down dev enp0s3

# 1
sudo ip addr flush dev enp0s3
sudo ip link set down dev enp0s3
```