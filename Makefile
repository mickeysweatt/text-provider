CC=g++
IDIR = /usr/local/Cellar/boost/1.58.0/include/
LDIR = /usr/local/Cellar/boost/1.58.0/lib/
SRCDIR = src
ODIR=obj

CFLAGS=-I$(IDIR) --std=c++0x
LFLAGS=-L$(LDIR) -lboost_system -lstdc++

_DEPS = server.h TextProviderProtocol.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ = main.o server.o TextProviderProtocol.o simple-local-cache-text-provider.o \
	   cache-protocol.o random-access-cache.o optimistic-prefetch-cache.o lru-cache.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

text-provider: $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~