CC=gcc
EXEC=semver.exe
SOURCE=semver.c utils.c

all:$(EXEC)

$(EXEC): $(SOURCE)
	$(CC) $^ -o $@
	
clean:
	rm -rf $(EXEC)
	
