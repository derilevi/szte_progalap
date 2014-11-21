SHELL=/bin/bash
CC=gcc
CFLAGS=-Wall -static -O2

all: check

feladat:	feladat.c
			$(CC) $(CFLAGS) -o $@ $<
check:		feladat
			@echo "$${PWD##*/}. feladat"; \
			i=1; \
			filename=ex$${i}.be; \
			while [ -f $$filename ]; do \
				cp ex$${i}.be be.txt; \
				./feladat; \
				if cmp -s ex$${i}.ki ki.txt ; then echo "$$i.teszt: Rendben" ; else echo "$$i.teszt: HIBA" ; fi; \
				rm -f be.txt ki.txt; \
				i=$$((i+1)); \
				filename=ex$${i}.be; \
			done
hiba:		feladat
			@echo "$${PWD##*/}. feladat"; \
			i=1; \
			hiba=0; \
			filename=ex$${i}.be; \
			while [ -f $$filename ]; do \
				cp ex$${i}.be be.txt; \
				./feladat; \
				if ! cmp -s ex$${i}.ki ki.txt ; then hiba=$$((hiba+1)) ; fi; \
				rm -f be.txt ki.txt; \
				i=$$((i+1)); \
				filename=ex$${i}.be; \
			done; \
			if [ $$hiba -eq 0 ] ; then echo -e "\033[1mHibátlan!\033[0m" ; else echo -e "\033[1mHIBÁS!\nHelyes/összes: "$$((i-hiba-1))/$$((i-1))"\033[0m"; fi;


.PHONY: clean
clean:
	@rm feladat
