### Do czego służy system plików proc(5) w systemie Linux?
Jest to virtualny system plików zawierający przydatne informacje o aktualnie uruchomionych procesach. Jest to "centrum" kontroli i iniformacji dla jądra.

### Dla wybranego przez siebie procesu o identyfikatorze pid wydrukuj zawartość katalogu «/proc/pid». Wyświetl plik zawierający argumenty programu oraz zmienne środowiskowe.
```
ls /proc/1707/

arch_status  comm                fd                 limits     mountstats     pagemap      sessionid     status          wchan
attr         coredump_filter     fdinfo             loginuid   net            patch_state  setgroups     syscall
autogroup    cpu_resctrl_groups  gid_map            map_files  ns             personality  smaps         task
auxv         cpuset              io                 maps       numa_maps      projid_map   smaps_rollup  timens_offsets
cgroup       cwd                 ksm_merging_pages  mem        oom_adj        root         stack         timers
clear_refs   environ             ksm_stat           mountinfo  oom_score      sched        stat          timerslack_ns
cmdline      exe                 latency            mounts     oom_score_adj  schedstat    statm         uid_map
```

- argumenty programu: argumenty wywołania programu, inaczej argc i argv, znajdują się w `/proc/[pid]/cmdline`.
```
cat /proc/1707/cmdline
/usr/bin/gnome-shell
```
- zmienne środowiskowe: zmienne dziedziczone od rodzica, które mogą być zmieniane przez użytkownika, służą do konfiguracji działania procesu np. gdzie mają być zapisywane pliki. Znajdują się w `/proc/[pid]/environ`.
```
cat /proc/1707/environ
HOME=/home/rafalLANG=en_US.UTF-8LC_ADDRESS=pl_PL.UTF-8LC_IDENTIFICATION=pl_PL.UTF-8LC_MEASUREMENT=pl_PL.UTF-8LC_MONETARY=pl_PL.UTF-8LC_NAME=pl_PL.UTF-8LC_NUMERIC=pl_PL.UTF-8LC_PAPER=pl_PL.UTF-8LC_TELEPHONE=pl_PL.UTF-8LC_TIME=pl_PL.UTF-8LOGNAME=rafalPATH=/home/linuxbrew/.linuxbrew/bin:/home/linuxbrew/.linuxbrew/sbin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin:/opt/nvim-linux64/binSHELL=/bin/bashSYSTEMD_EXEC_PID=1707USER=rafalXDG_RUNTIME_DIR=/run/user/1000GTK_MODULES=gail:atk-bridgeQT_ACCESSIBILITY=1XDG_DATA_DIRS=/usr/share/ubuntu:/usr/local/share/:/usr/share/:/var/lib/snapd/desktopCONDA_PROMPT_MODIFIER=falseDBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/busDESKTOP_SESSION=ubuntuGDMSESSION=ubuntuGNOME_DESKTOP_SESSION_ID=this-is-deprecatedGNOME_SHELL_SESSION_MODE=ubuntuHOMEBREW_CELLAR=/home/linuxbrew/.linuxbrew/CellarHOMEBREW_PREFIX=/home/linuxbrew/.linuxbrewHOMEBREW_REPOSITORY=/home/linuxbrew/.linuxbrew/HomebrewIM_CONFIG_PHASE=1INFOPATH=/home/linuxbrew/.linuxbrew/share/info:MANPATH=/home/linuxbrew/.linuxbrew/share/man:POSH_PID=1584POSH_SHELL_VERSION=5.1.16(1)-releasePOSH_THEME=/home/linuxbrew/.linuxbrew/opt/oh-my-posh/themes/atomicBit.omp.jsonPOWERLINE_COMMAND=oh-my-poshPWD=/home/rafalQT_IM_MODULE=ibusSESSION_MANAGER=local/rafal-ThinkPad-X13-Yoga-Gen-1:@/tmp/.ICE-unix/1674,unix/rafal-ThinkPad-X13-Yoga-Gen-1:/tmp/.ICE-unix/1674SHLVL=0SSH_AGENT_LAUNCHER=gnome-keyringSSH_AUTH_SOCK=/run/user/1000/keyring/sshUSERNAME=rafalXDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdgXDG_CURRENT_DESKTOP=ubuntu:GNOMEXDG_MENU_PREFIX=gnome-XDG_SESSION_CLASS=userXDG_SESSION_DESKTOP=ubuntuXDG_SESSION_TYPE=waylandXMODIFIERS=@im=ibus_=/usr/bin/gnome-sessionNOTIFY_SOCKET=/run/user/1000/systemd/notifyMANAGERPID=1474INVOCATION_ID=d602cc7b13364f9d89946057c66c3911JOURNAL_STREAM=8:11971
```

### Podaj znaczenie następujących pól pliku «status»: Uid, Gid, Groups, VmPeak, VmSize, VmRSS, Threads, voluntary_ctxt_switches, nonvoluntary_ctxt_switches