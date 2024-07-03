CC = gcc
CFLAGS = -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 $(shell pkg-config --cflags --libs poppler-glib)

SRCS = getPhraseAndAddress.c algoritmoTrejos.c printResults.c main.c
OBJS = $(SRCS:.c=.o)

all: main

main: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	@rm -f main $(OBJS)
