CC=g++
EXEC=qudp.exe
SOURCE=qudp.cpp
EXEC2=qudps.exe
SOURCE2=qudps.cpp

all:$(EXEC) $(EXEC2)

$(EXEC): $(SOURCE)
	$(CC) $^ -o $@ -lstdc++ -lwsock32
  
$(EXEC2): $(SOURCE2)
	$(CC) $^ -o $@ -lstdc++ -lwsock32
	
clean:
	rm -rf $(EXEC) $(EXEC2)
	
