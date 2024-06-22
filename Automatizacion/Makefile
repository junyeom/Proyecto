CC = gcc
CFLAGS = -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS = getPhraseAndAddress.c searchPhrase.c printResults.c main.c
OBJS = $(SRCS:.c=.o)

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f main $(OBJS)