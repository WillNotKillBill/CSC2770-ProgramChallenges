CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm
SRCS = NTP_Client.c
OBJS = $(SRCS:.c=.o)
TARGET = Challenge3

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
