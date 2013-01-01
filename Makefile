CC=g++
CFLAGS=-Wall -pedantic
LDFLAGS=-lGL -lGLU -lglut

DEPS=octree_fn.h
OBJ=octree.o octree_fn.o

all: octree

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

octree: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	 rm -f *~ *.o octree
