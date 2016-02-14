#Compiler
	CC=gcc

#CFLAGS
	CFLAGS= -g -Wall
	
index: tokenizer.o sorted-list.o index.o 
	$(CC) $(CFLAGS) -o $@ $^
	
index.o: index.c tokenizer.h sorted-list.h
	$(CC) -c $(CFLAGS) index.c

tokenizer.o: tokenizer.h tokenizer.c sorted-list.h
	$(CC) -c $(CFLAGS) tokenizer.h tokenizer.c 
	
sorted-list.o: sorted-list.c sorted-list.h
	$(CC) -c $(CFLAGS) sorted-list.h sorted-list.c
	
#clean
clean:
	rm -f *.o index
