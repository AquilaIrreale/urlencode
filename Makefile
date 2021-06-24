.PHONY: all

CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic
LDFLAGS=

all: urlencode

urlencode: urlencode.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f urlencode
