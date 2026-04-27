.PHONY: clean all

all: Stack.o vector.o flist.o
	g++ Stack.o flist.o vector.o -o stack_test -L. -lStackTest

Stack.o: stack.cpp Stack.h StackImplementation.h flist.h Vector.h
	g++ -c stack.cpp -o Stack.o
flist.o: flist.cpp flist.h 
	g++ -c flist.cpp -o flist.o
vector.o: Vector.cpp Vector.h
	g++ -c Vector.cpp -o vector.o

clean:
	rm -f Stack.o flist.o vector.o
