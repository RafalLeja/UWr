## 1.
```bash
adduser jantest
```

## 2.
```bash
adduser jantest cdrom
adduser jantest audio
adduser jantest bluetooth
```

## 3.
```bash
jantest ALL= (root) sudo /usr/sbin/ip
```

## 4.
```bash
addgroup projekt
adduser jantest projekt
adduser rafal projekt
```

## 5.
```bash
groups
```

## 6.
```bash
jantest ALL= (rafal) /usr/bin/whoami
```

## 7.
```bash
nvim /etc/login.defs

CHFN_RESTRICT frwh
```
