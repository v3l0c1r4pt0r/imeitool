CC=gcc
LD=gcc
CFLAGS?=-Wall
LDFLAGS=
LIBS=

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
OUTFILE=imeitool

all: $(OUTFILE)
$(OUTFILE): $(OBJ)
	$(LD) $(LDFLAGS) $(LIBS) $(OBJ) -o $@
%.o: %.c
	$(CC) -c $(CFLAGS) $<
clean:
	rm -vfr $(OBJ) $(OUTFILE)
.PHONY: $(OUTFILE) clean
