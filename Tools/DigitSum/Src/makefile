CC=gcc
EXEC=digitsum.exe
SOURCE=digitsum.cpp version.h

all:$(EXEC)

$(EXEC): $(SOURCE)
	$(CC) $^ -o $@ -lstdc++
	
clean:
	rm -rf $(EXEC)
	
