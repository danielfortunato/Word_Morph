CC=gcc
CFLAGS= -Wall -ansi -g

wordmorph: wordmorph.o file.o table.o graph.o LinkedList.o heap.o
	$(CC) $(CFLAGS) -o wordmorph wordmorph.o file.o heap.o table.o graph.o LinkedList.o -lm

wordmorph.o: wordmorph.c file.h table.h
	$(CC) -c $(CFLAGS) wordmorph.c

file.o: file.c file.h table.h
	$(CC) -c $(CFLAGS) file.c

table.o: table.c table.h
		$(CC) -c $(CFLAGS) table.c

graph.o: graph.c graph.h defs.h LinkedList.h table.h
		$(CC) -c $(CFLAGS) graph.c

heap.o: heap.c LinkedList.h table.h heap.h graph.h file.h
		$(CC) -c $(CFLAGS) heap.c

LinkedList.o: LinkedList.c LinkedList.h
		$(CC) -c $(CFLAGS) LinkedList.c

clean::
	rm -f *.o core a.out wordmorph *~
