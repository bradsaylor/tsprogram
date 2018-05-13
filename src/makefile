#taken from tutorial @ http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =../include
CC=gcc
CFLAGS=-g -I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS=-lm


_DEPS = tsp.h init.h menu_funcs.h debug.h util.h tsp_display.h tsp_file_func_utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tsp.o init.o menu_funcs.o debug.o util.o tsp_display.o tsp_file_func_utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tsp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
