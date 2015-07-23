CC = gcc

CFLAGS = -Wall -Wextra -O2
CFLAGS += -I../include 
CFLAGS += -L../lib

EXEC = idents.exe

SOURCE = idents.c


all:$(EXEC)

$(EXEC): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@ -lstdc++ -lcii
	
clean:
	rm -rf $(EXEC)
	
