CC=g++
EXE_UDPC=udpc.exe
SRC_UDPC=udpc.cpp
EXE_UDPS=udps.exe
SRC_UDPS=udps.cpp

all:$(EXE_UDPC) $(EXE_UDPS)

$(EXE_UDPC): $(SRC_UDPC)
	$(CC) $^ -static -o $@ -lstdc++ -lwsock32
  
$(EXE_UDPS): $(SRC_UDPS)
	$(CC) $^ -static -o $@ -lstdc++ -lwsock32
	
clean:
	rm -rf $(EXE_UDPC) $(EXE_UDPS)
	
