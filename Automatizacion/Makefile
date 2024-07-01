CC = gcc
CFLAGS = -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS = getPhraseAndAddress.c printResults.c main.c
OBJS = $(SRCS:.c=.o)

all: main

main: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	@rm -f main $(OBJS)
