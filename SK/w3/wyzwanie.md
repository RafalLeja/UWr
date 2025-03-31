# 1
```
sudo ip link set enp0s3 name enp-loc0
sudo ip addr add dev enp-loc0 192.168.0.1/24
sudo ip link set enp-loc0 up
sudo ip route add default via 192.168.0.2
```


# 2
```
sudo ip link set enp0s3 name enp-loc0
sudo ip addr add dev enp-loc0 192.168.0.2/24
sudo ip link set enp-loc0 up
sudo ip link set enp0s8 name enp-loc1
sudo ip addr add dev enp-loc1 192.168.1.2/24
sudo ip link set enp-loc1 up
sudo ip link set enp0s9 name enp-loc2
sudo ip addr add dev enp-loc2 192.168.2.2/24
sudo ip link set enp-loc2 up
```

# 3
```
sudo ip link set enp0s3 name enp-loc1
sudo ip addr add dev enp-loc1 192.168.1.3/24
sudo ip link set enp-loc1 up
sudo ip link set enp0s8 name enp-loc3
sudo ip addr add dev enp-loc3 192.168.3.3/24
sudo ip link set enp-loc3 up
```

# 4
```
sudo ip link set enp0s3 name enp-loc2
sudo ip addr add dev enp-loc2 192.168.2.4/24
sudo ip link set enp-loc2 up
sudo ip link set enp0s8 name enp-loc3
sudo ip addr add dev enp-loc3 192.168.3.4/24
sudo ip link set enp-loc3 up
sudo ip link set enp0s9 name enp-loc4
sudo ip addr add dev enp-loc4 192.168.4.4/24
sudo ip link set enp-loc4 up
```

# 5
```
sudo ip link set enp0s3 name enp-loc4
sudo ip addr add dev enp-loc4 192.168.4.5/24
sudo ip link set enp-loc4 up
sudo ip route add default via 192.168.4.4
```

# 2
```
sudo sed -i -e 's/ripd=no/ripd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router rip
network enp-loc0
network enp-loc1
network enp-loc2
end
show running-config
copy running-config startup-config
```

# 3
```
sudo sed -i -e 's/ripd=no/ripd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router rip
network enp-loc1
network enp-loc3
end
show running-config
copy running-config startup-config
```

# 4
```
sudo sed -i -e 's/ripd=no/ripd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router rip
network enp-loc2
network enp-loc3
network enp-loc4
end
show running-config
copy running-config startup-config
```

# 1
```
ping 196.168.4.5

traceroute 196.168.4.5
```

