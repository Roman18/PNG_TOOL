CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
SRC=main.c rw.c
png: $(SRC)
	$(CC) -o png $(SRC) $(CFLAGS)