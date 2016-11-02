CC = gcc
CFLAGS  = -g -Wall

default: install

install:
	$(CC) $(CFLAGS) -o pstree main.c utils.c process.c process_node.c

clean:
	$(RM) pstree *.o *~
