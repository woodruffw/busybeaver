CC = cc
CFLAGS = -O3 -std=c99 -Wall -Wextra -pedantic

SRCS = $(wildcard ./src/*.c)
OBJS = $(SRCS:.c=.o)
EXE = busybeaver

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ./$(EXE)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(EXE)

.PHONY: all clean