############################################################################
# Makefile for run length encode/decode library and sample program
############################################################################
CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -Wextra -pedantic -ansi -c
LDFLAGS = -O3 -o

# libraries
LIBS = -L. -Loptlist -lrle -loptlist

# Treat NT and non-NT windows the same
ifeq ($(OS),Windows_NT)
	OS = Windows
endif

ifeq ($(OS),Windows)
	EXE = .exe
	DEL = del
else	#assume Linux/Unix
	EXE =
	DEL = rm -f
endif

all:		sample$(EXE)

sample$(EXE):	sample.o librle.a optlist/liboptlist.a
		$(LD) $< $(LIBS) $(LDFLAGS) $@

sample.o:	sample.c rle.h optlist/optlist.h
		$(CC) $(CFLAGS) $<

librle.a:	rle.o vpackbits.o
		ar crv $@ $^
		ranlib $@

rle.o:		rle.c
		$(CC) $(CFLAGS) $<

vpackbits.o:	vpackbits.c
		$(CC) $(CFLAGS) $<

optlist/liboptlist.a:
		cd optlist && $(MAKE) liboptlist.a

clean:
		$(DEL) *.o
		$(DEL) *.a
		$(DEL) sample$(EXE)
		cd optlist && $(MAKE) clean
