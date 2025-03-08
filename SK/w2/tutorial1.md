## Na maszynie Virbian1 ustal interfejs enpx sy połączony z siecią remote oraz interfejs enpw sz połączony połączony z siecią local1. Dla wygody zmienimy nazwy tych interfejsów poleceniami:

```bash
# V0
sudo ip link set enp0s3 name enp-rem
sudo ip link set enp0s8 name enp-loc

# V1
sudo ip link set enp0s3 name enp-rem
sudo ip link set enp0s8 name enp-loc
```

## Poleceniem ip link aktywuj karty enp-rem a poleceniem ip addr przypisz im adresy IP. Na maszynie Virbian1 przypisz tej karcie adres IP równy 172.16.0.1/16, zaś na maszynie Virbian2 adres 172.16.0.2/16. Poleceniem ip addr wyświetl aktualnie skonfigurowane interfejsy. W przypadku błędu wykorzystaj polecenie ip addr flush.

```bash
# V0
sudo ip link set up enp-rem
sudo ip addr add 172.16.0.1/16 dev enp-rem

#V1
sudo ip link set up enp-rem
sudo ip addr add 172.16.0.2/16 dev enp-rem

## Wyświetl tablicę routingu poleceniem

```bash
ip route

route -n
```

## Za pomocą programu ping sprawdź, czy połączone ze sobą siecią remote maszyny wirtualne Virbian1 i Virbian2 „widzą się” wzajemnie.

```bash
# V0
ping 172.16.0.1

# V1
ping 172.16.0.2
```

## Pingnij adres interfejsu pętli lokalnej lo o adresie 127.0.0.1. Zauważ, że komunikaty dochodzą pomimo tego, że odpowiedni wpis nie jest wyświetlany poleceniem ip route. Te dodatkowe wpisy w tablicy można wyświetlić poleceniem

```bash
# V0
ping 127.0.0.2

# V1
ping 127.0.0.1

ip route list table local
```
## Na maszynach Virbian1 i Virbian2 włącz Wiresharka i rozpocznij nasłuchiwanie na wszystkich interfejsach. Zaobserwuj, co jest wypisywane w konsoli oraz jakie pakiety są wysyłane i odbierane jeśli pingasz z maszyny Virbian1 :

```bash
# V0
ping 127.0.0.1

ping 172.16.0.1

ping 172.16.0.2

ping -b 172.16.255.255

ping 172.16.0.0/16

ping 10.10.10.10
```