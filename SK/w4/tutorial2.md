# 1
```
sudo sed -i -e 's/ospfd=no/ospfd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router ospf
network 192.168.4.0/24 area 0
network 192.168.1.0/24 area 0
end
show running-config
copy running-config startup-config
show ip route
```

# 2
```
sudo sed -i -e 's/ospfd=no/ospfd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router ospf
network 192.168.1.0/24 area 0
network 192.168.2.0/24 area 0
end
show running-config
copy running-config startup-config
show ip route
```

# 3
```
sudo sed -i -e 's/ospfd=no/ospfd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router ospf
network 192.168.2.0/24 area 0
network 192.168.3.0/24 area 0
end
show running-config
copy running-config startup-config
show ip route
```

# 4
```
sudo sed -i -e 's/ospfd=no/ospfd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh

configure terminal
router ospf
network 192.168.3.0/24 area 0
network 192.168.4.0/24 area 0
end
show running-config
copy running-config startup-config
show ip route
```

================================

# 1
```
sudo ip addr add dev enp-all 172.16.16.1/16
sudo ip link set enp-all up
sudo vtysh

configure terminal
router ospf
network 172.16.16.1/16 area 0
end
show running-config
copy running-config startup-config
show ip route
```

# 2
```
sudo ip addr add dev enp-all 172.16.16.2/16
sudo ip link set enp-all up
sudo vtysh

configure terminal
router ospf
network 172.16.16.2/16 area 0
end
show running-config
copy running-config startup-config
show ip route
```

# 3
```
sudo ip addr add dev enp-all 172.16.16.3/16
sudo ip link set enp-all up
sudo vtysh

configure terminal
router ospf
network 172.16.16.3/16 area 0
end
show running-config
copy running-config startup-config
show ip route
```

# 4
```
sudo ip addr add dev enp-all 172.16.16.4/16
sudo ip link set enp-all up
sudo vtysh

configure terminal
router ospf
network 172.16.16.4/16 area 0
end
show running-config
copy running-config startup-config
show ip route
```


=================================

# 1
```bash
sudo ip link set enp-rem4 down
sudo ip link set enp-all down
```

# 2
```bash
sudo ip link set enp-rem2 down
```

# 3
```bash
sudo ip link set enp-all down
```

# 4
```bash
sudo ip link set enp-rem4 down
```

==========================

# 1
```bash
sudo vtysh

show ip route 192.168.2.0/24
```