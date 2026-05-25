.PHONY: clean
all: Bst.o
	g++ Bst.o -o bst_test -L. -lBSTTest

Bst.o: bst.cpp BST.h
	g++ -c bst.cpp -o Bst.o

clean:
	rm -f Bst.o
