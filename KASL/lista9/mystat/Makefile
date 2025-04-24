PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
SYSTEMD_DIR=/etc/systemd/system
LOGDIR=/var/log
STATEDIR=/var/lib/mystat

all: mystat

mystat: mystat.c
	$(CC) -o mystat mystat.c

install: all
	install -Dm755 mystat $(BINDIR)/mystat
	install -Dm755 mystat-graph.sh $(BINDIR)/mystat-graph.sh

	# Instalacja jednostek systemd
	install -Dm644 mystat.service $(SYSTEMD_DIR)/mystat.service
	install -Dm644 mystat-graph.service $(SYSTEMD_DIR)/mystat-graph.service
	install -Dm644 mystat-graph.timer $(SYSTEMD_DIR)/mystat-graph.timer

	# Tworzenie katalogów na dane
	mkdir -p $(STATEDIR)
	touch $(LOGDIR)/mystat.log
	chmod 644 $(LOGDIR)/mystat.log

	# Przeładowanie systemd i aktywacja usług
	systemctl daemon-reload
	systemctl enable mystat.service
	systemctl enable mystat-graph.timer
	systemctl start mystat.service
	systemctl start mystat-graph.timer

clean:
	rm -f mystat

uninstall:
	rm -f $(BINDIR)/mystat
	rm -f $(BINDIR)/mystat-graph.sh
	rm -f $(SYSTEMD_DIR)/mystat.service
	rm -f $(SYSTEMD_DIR)/mystat-graph.service
	rm -f $(SYSTEMD_DIR)/mystat-graph.timer
	systemctl daemon-reload
	systemctl disable mystat.service || true
	systemctl disable mystat-graph.timer || true
	systemctl stop mystat.service || true
	systemctl stop mystat-graph.timer || true
