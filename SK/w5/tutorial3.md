## 1.
```bash
ping 192.168.0.2
```

## 2.
```bash
sudo ip addr del 192.168.0.2/24 dev enp0 && sudo ip addr add 192.168.0.123/24 dev enp0
```
