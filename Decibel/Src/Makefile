CC=gcc
EXEC=db2pr.exe
SOURCE=db2pr.cpp

all:$(EXEC)

$(EXEC): $(SOURCE)
	$(CC) $^ -o $@ -lstdc++
	
clean:
	rm -rf $(EXEC)
	
