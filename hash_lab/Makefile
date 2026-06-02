.PHONY: clean
all: HashTable.o
	g++ HashTable.o -o hashtable_test -L. -lHashTest

Bst.o: HashTable.cpp HashTable.h
	g++ -c HashTable.cpp -o HashTable.o

clean:
	rm -f HashTable.o
