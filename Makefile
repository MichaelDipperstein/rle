############################################################################
# Makefile for run length encode/decode library and sample program
#
#   $Id: Makefile,v 1.4 2007/09/08 17:07:26 michael Exp $
#   $Log: Makefile,v $
#   Revision 1.4  2007/09/08 17:07:26  michael
#   Replace getopt with optlist.
#
#   Revision 1.3  2007/07/16 02:19:49  michael
#   Use -pedantic option when compiling.
#
#   Revision 1.2  2006/09/10 05:07:18  michael
#   Add packbits variant
#   Compile compress/decompress and optlist functions as libraries.
#
#   Revision 1.1.1.1  2004/05/03 03:56:49  michael
#   Initial version
#
#
############################################################################
CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -pedantic -ansi -c
LDFLAGS = -O3 -o

# libraries
LIBS = -L. -lrle -loptlist

# Treat NT and non-NT windows the same
ifeq ($(OS),Windows_NT)
	OS = Windows
endif

ifeq ($(OS),Windows)
	EXE = .exe
	DEL = del
else	#assume Linux/Unix
	EXE =
	DEL = rm
endif

all:		sample$(EXE)

sample$(EXE):	sample.o librle.a liboptlist.a
		$(LD) $< $(LIBS) $(LDFLAGS) $@

sample.o:	sample.c rle.h optlist.h
		$(CC) $(CFLAGS) $<

librle.a:	rle.o vpackbits.o
		ar crv $@ $^
		ranlib $@

rle.o:		rle.c
		$(CC) $(CFLAGS) $<

vpackbits.o:	vpackbits.c
		$(CC) $(CFLAGS) $<

liboptlist.a:	optlist.o
		ar crv $@ $^
		ranlib $@

optlist.o:	optlist.c optlist.h
		$(CC) $(CFLAGS) $<

clean:
		$(DEL) *.o
		$(DEL) *.a
		$(DEL) sample$(EXE)
