############################################################################
# Makefile for run length encode/decode library and sample program
#
#   $Id: Makefile,v 1.2 2006/09/10 05:07:18 michael Exp $
#   $Log: Makefile,v $
#   Revision 1.2  2006/09/10 05:07:18  michael
#   Add packbits variant
#   Compile compress/decompress and getopt functions as libraries.
#
#   Revision 1.1.1.1  2004/05/03 03:56:49  michael
#   Initial version
#
#
############################################################################
CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -ansi -c
LDFLAGS = -O3 -o

# libraries
LIBS = -L. -lrle -lgetopt

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

sample$(EXE):	sample.o librle.a libgetopt.a
		$(LD) $< $(LIBS) $(LDFLAGS) $@

sample.o:	sample.c rle.h getopt.h
		$(CC) $(CFLAGS) $<

librle.a:	rle.o vpackbits.o
		ar crv $@ $^
		ranlib $@

rle.o:		rle.c
		$(CC) $(CFLAGS) $<

vpackbits.o:	vpackbits.c
		$(CC) $(CFLAGS) $<

libgetopt.a:	getopt.o
		ar crv $@ $^
		ranlib $@

getopt.o:	getopt.c getopt.h
		$(CC) $(CFLAGS) $<

clean:
		$(DEL) *.o
		$(DEL) *.a
		$(DEL) sample$(EXE)
