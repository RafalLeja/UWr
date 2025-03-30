# 2
```
sudo sed -i -e 's/ripd=no/ripd=yes/g' /etc/frr/daemons
sudo systemctl start frr
sudo vtysh
```

```
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
```

```
configure terminal
router rip
network 192.168.2.0/24
network 192.168.3.0/24
end

show running-config
copy running-config startup-config

show ip rip status
```

```
ip route
```

# 4
```
traceroute 192.168.1.1
```
