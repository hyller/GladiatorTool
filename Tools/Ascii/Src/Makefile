CC=gcc
EXEC=ascii.exe
SOURCE=main.cpp ascii.cpp ascii.h version.h

all:$(EXEC)

$(EXEC): $(SOURCE)
	$(CC) $^ -o $@ -lstdc++
	
clean:
	rm -rf $(EXEC)
	
