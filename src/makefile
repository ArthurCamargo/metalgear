IDIR =../include
CC =gcc 
CFLAGS =-I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS=-lm -lncurses

_DEPS = game.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS)) 

_OBJ = game.o gamefunc.o imprime.o inimigos.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ) 
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean: 
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
