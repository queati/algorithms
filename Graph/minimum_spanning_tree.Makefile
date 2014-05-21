minimum_spanning_tree: minimum_spanning_tree.o kruskal.o quickSort.o \
			prim.o heapSort.o
	cc -o minimum_spanning_tree minimum_spanning_tree.o kruskal.o \
				quickSort.o prim.o heapSort.o

minimum_spanning_tree.o: minimum_spanning_tree.c minimum_spanning_tree.h \
						 macros.h
	cc -c -Wall -g minimum_spanning_tree.c

kruskal.o: kruskal.c macros.h minimum_spanning_tree.h
	cc -c -Wall -g kruskal.c

quickSort.o: quickSort.c macros.h
	cc -c -Wall -g quickSort.c

prim.o: prim.c macros.h
	cc -c -Wall -g prim.c

heapSort.o: heapSort.c
	cc -c -Wall -g heapSort.c

.PHONY: clean
clean:
	rm -f minimum_spanning_tree *.o

