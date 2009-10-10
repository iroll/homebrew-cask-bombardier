CC=gcc
CFLAGS=-Wall -g -Werror -O2
LDFLAGS=-lncurses -g
OBJS=bombardier.o display.o date.o randomhouse.o step.o hof.o signal.o gcurses.o
DESTDIR=/

all: bombardier

bombardier: texts.h $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

texts.h: texts.en
	./txttotextsh.pl <texts.en >texts.h

clean:
	rm -f $(OBJS) bombardier texts.h

$(OBJS): *.h VERSION

install:
	install -d $(DESTDIR)/usr/games
	install bombardier $(DESTDIR)/usr/games
	chgrp games $(DESTDIR)/usr/games/bombardier
	chmod 2755 $(DESTDIR)/usr/games/bombardier
	install -d $(DESTDIR)/var/games/bombardier
	chgrp games $(DESTDIR)/var/games/bombardier
	chmod 775 $(DESTDIR)/var/games/bombardier
	install -d $(DESTDIR)/usr/share/man/man6
	install bombardier.6 $(DESTDIR)/usr/share/man/man6

