## 1.
```bash
evince&

ps -eo pid,ppid,comm | less
```

## 3.
```bash
evince&

jobs
disown %1
jobs

ps -eo pid,ppid,comm | less
```

## 5.
```bash
evince&

shopt -s huponexit

exit
```

## 6.
```bash
bash -l

evince&

shopt -s huponexit

exit
```

## 7.
```bash
