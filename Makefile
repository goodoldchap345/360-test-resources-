CC=gcc
CFLAGS=-g -Werror -Wall

all: one two threeServer fourClient

one: one.c
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

two: two.c
	$(CC) $(CFLAGS) -o $@ $^

threeServer: threeServer.c
	$(CC) $(CFLAGS) -o $@ $^

fourClient: fourClient.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f one two threeServer fourClient

.PHONY: all clean
