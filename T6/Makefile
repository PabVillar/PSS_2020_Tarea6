CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g
LDLIBS= -lpthread

all: test-t6

test-t6.o t6.o: suma.h

test-t6: t6.o test-t6.o

clean:
	rm -f *.o
	rm -f test-t6
