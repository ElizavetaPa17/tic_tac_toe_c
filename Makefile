CC := gcc
CFLAGS := -Wall -Werror -g -O2 

SRCDIR   := src
HEADDIR  := include
BINDIR   := bin
BUILDDIR := build

BIN := $(BINDIR)/tic-tac-toe
INCLUDES := -I./$(HEADDIR)/module
LDFLAGS := -lncurses

all: $(BIN)

$(BIN): main.o internal.o draw.o
	$(CC) -o $(BIN) main.o internal.o draw.o $(LDFLAGS)

main.o: $(SRCDIR)/core/main.c 
	$(info someinfo)
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

%.o: $(SRCDIR)/module/%.c 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm -f *.o

.phony: clean all