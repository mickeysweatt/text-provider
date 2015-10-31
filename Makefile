CC=g++
IDIR = /usr/local/Cellar/boost/1.58.0/include/
LDIR = /usr/local/Cellar/boost/1.58.0/lib/
SRCDIR = src
ODIR=obj

CFLAGS=-I$(IDIR) --std=c++11
LFLAGS=-L$(LDIR) -lboost_system -lstdc++

_DEPS = server.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ = main.o server.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

text-provider: $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~