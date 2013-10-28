CC=gcc 
CFLAGS=-c -g -Wall
LDFLAGS=-lm
SRC=momsim.c
OBJ=$(SRC:.c=.o)
EXE=momsim
HEADS=

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@
%.o: %.c $(HEADS)
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf $(OBJ) $(EXE)
