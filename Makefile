CC := gcc
CFLAGS := -Wall -Werror -g -O2 

SRCDIR   := src
HEADDIR  := include
BINDIR   := bin
BUILDDIR := build

BIN := $(BINDIR)/tic-tac-toe
INCLUDES := -I./$(HEADDIR)/module
LDFLAGS := -lncurses -lmenu -lpanel

all: $(BIN) statistic_file

$(BIN): main.o internal.o draw.o constants.o
	$(CC) -o $(BIN) $? $(LDFLAGS)

main.o: $(SRCDIR)/core/main.c 
	$(info someinfo)
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

%.o: $(SRCDIR)/module/%.c 
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

statistic_file:
	touch $(BINDIR)/statistic_file
	echo "PLAYERS\n\tPlayer\tGamesCount\tWins\n\t0\t\t0\t\t0" \
		 "\nGENERAL\n\tTotalGames\n\t0" > $(BINDIR)/statistic_file

clean:
	rm -f *.o

.phony: clean all