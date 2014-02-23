CC=gcc 
CFLAGS=-c -O3 -Wall
LDFLAGS=-lm
SRC=main.c thrust.c drag.c ldairfoil.c lift.c takeoffd.c checkstab.c moment.c momsim.c
OBJ=$(SRC:.c=.o)
EXE=wingop
HEADS=wingop.h

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@
%.o: %.c $(HEADS)
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf $(OBJ) $(EXE)
