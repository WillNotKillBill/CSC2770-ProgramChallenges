CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: HTTP_Server

HTTP_Server: HTTP_Server.c
	$(CC) $(CFLAGS) -o HTTP_Server HTTP_Server.c

clean:
	rm -f HTTP_Server
