# 1
```
sudo ip addr add dev enp-rem4 192.168.4.1/24
sudo ip link set enp-rem4 up
sudo ip route del default
sudo ip route
```

# 4
```
sudo ip addr add dev enp-rem4 192.168.4.4/24
sudo ip link set enp-rem4 up
sudo ip route del default
sudo ip route
```

# 1
```
sudo sed -i -e 's/ripd=no/ripd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router rip
network 192.168.4.0/24
network 192.168.1.0/24
end
show running-config
copy running-config startup-config
```

# 2
```
sudo sed -i -e 's/ripd=no/ripd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router rip
network 192.168.1.0/24
network 192.168.2.0/24
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
network 192.168.2.0/24
network 192.168.3.0/24
end
show running-config
copy running-config startup-config
```

# 1 2 3
``` 
show ip rip
```

# 4
```
sudo sed -i -e 's/ripd=no/ripd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router rip
network 192.168.3.0/24
network 192.168.4.0/24
end
show running-config
copy running-config startup-config
```

# 2
```
sudo ip link set down dev enp-rem2

sudo ip link set up dev enp-rem2
```

