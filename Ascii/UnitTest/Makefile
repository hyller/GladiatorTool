CC = g++

CFLAGS += -D_MSC_VER=1300
CFLAGS += -I../../Components  \
          -I../../Components/CppUnit/cppunit-1.10.2/include \
          -I../../Ascii/Src
CFLAGS += -L../../Components/CppUnit/cppunit-1.10.2/lib

EXEC = ascii_u.exe

SOURCE = ./main.cpp  \
         ./Scripts/FormatOutputSpy.cpp ./Scripts/FormatOutputSpy.h \
		     ./Scripts/TestAscii.cpp  ./Scripts/TestAscii.h  \
		     ../Src/ascii.cpp ../Src/ascii.h


all:$(EXEC)

$(EXEC): $(SOURCE)
	$(CC) $(CFLAGS) $^ -o $@ -lstdc++ -lCppUnitBuild
	
clean:
	rm -rf $(EXEC)
	
