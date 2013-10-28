CC=gcc 
CFLAGS=-c -g -Wall
LDFLAGS=-lm
SRC=momsim.c ../lift.c ../drag.c
OBJ=$(SRC:.c=.o)
EXE=momsim
HEADS=../wingop.h

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@
%.o: %.c $(HEADS)
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf $(OBJ) $(EXE)
