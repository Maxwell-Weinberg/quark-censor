CC=gcc
CFLAGS=-I.

censor: censor.c
	$(CC) -o censor censor.c
