# Bombardier
# The GNU Bombing utility
# Copyright (C) 2001, 2009 Gergely Risko
# Can be licensed under the terms of GPL v3 or above

CC=gcc
CFLAGS=-Wall -g -O2 -pedantic
LDFLAGS=-lncurses -g
OBJS=bombardier.o display.o date.o randomhouse.o step.o hof.o signal.o gcurses.o
DESTDIR=/

all: bombardier

bombardier: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) bombardier

$(OBJS): *.h VERSION texts.h

install:
	install -d $(DESTDIR)/usr/games
	install bombardier $(DESTDIR)/usr/games
	chgrp games $(DESTDIR)/usr/games/bombardier
	chmod 2755 $(DESTDIR)/usr/games/bombardier
	install -d $(DESTDIR)/var/games/bombardier
	chgrp games $(DESTDIR)/var/games/bombardier
	chmod 0755 $(DESTDIR)/var/games/bombardier
	install bdscore $(DESTDIR)/var/games/bombardier
	chgrp games $(DESTDIR)/var/games/bombardier/bdscore
	chown root $(DESTDIR)/var/games/bombardier/bdscore
	chmod 0664 $(DESTDIR)/var/games/bombardier/bdscore
	install -d $(DESTDIR)/usr/share/man/man6
	install bombardier.6 $(DESTDIR)/usr/share/man/man6
