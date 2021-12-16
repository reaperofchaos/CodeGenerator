#project name
NAME=CodeGenerator
# change application name  (executable output name)
TARGET=build/CodeGenerator

CMDTARGET=build/CodeGenerator
# compiler
CC=g++
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

#POSIX Thread library
PTHREAD=-lpthread

#winapi
WINAPI=-mwindows
SHLWAPI=-lshlwapi
COMDLG32=-lcomdlg32
#google test suite
GOOGLETEST=-lgtest -lgtest_main
CPPVERSION=-std=c++17

#MONGDB
MONGO=$$(pkg-config --libs --cflags libmongoc-1.0)
#MYSQL
MYSQL=-I"C:\Program Files\MySQL\MySQL Connector C++ 8.0\include\jdbc" -L"C:\Program Files\MySQL\MySQL Connector C+ 8.0\lib64"
#SQLITE
SQLITE=-l sqlite3

CMDCCFLAGS=$(CPPVERSION) $(DEBUG) $(OPT) $(WARN)
# linker
LD=g++

#LDFLAGS= -export-dynamic

GUIOBJS=winmain.o \


GUIOBJSDIR = objs/winmain.o \


CMDOBJS=main.o \
		FileReader.o\
		FileCreator.o\

CMDOBJSDIR=objs/main.o \
		   objs/FileReader.o \
		   objs/FileCreator.o

all: $(OBJS)
	make cmd

cmd: $(CMDOBJS)
	$(LD) -o $(CMDTARGET) $(CMDOBJSDIR) $(CMDCCFLAGS)
	
FileCreator.o:
	$(CC) -c $(CMDCCFLAGS) src/FileCreator.cpp -o objs/FileCreator.o

FileReader.o:
	$(CC) -c $(CMDCCFLAGS) src/FileReader.cpp -o objs/FileReader.o

main.o:
	$(CC) -c $(CMDCCFLAGS) src/main.cpp -o objs/main.o

run:
	cp test.cpp build/test.cpp
	./$(CMDTARGET) test.cpp -o  newTest.cpp

clean:
	rm -f objs/*.o $(TARGET)
