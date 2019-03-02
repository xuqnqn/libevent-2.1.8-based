
CC		= gcc
CFLAGS 	= -g -O0
LDFLAGS = -levent

all: server client

server : server.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

client : client.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
