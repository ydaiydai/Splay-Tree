# Makefile 

CXX = clang++

SplayTree: SplayTree.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f *.o SplayTree
