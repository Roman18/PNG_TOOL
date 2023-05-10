CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

png: main.c
	$(CC) -o png main.c $(CFLAGS)