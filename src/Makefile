CC=g++
PROJECT=notes
SOURCES=notes.cpp main.cpp
HEADERS=notes.h
OBJECTS=notes.o main.o
CFLAGS=-Wall -Werror -Wextra -std=c++17

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	CHECKFLAGS=-lgtest
	OUTFILENAME=notes.app
else
	CHECKFLAGS=-lgtest -lpthread -lrt -lm -lsubunit -ldl
	OUTFILENAME=notes
endif

all: install

install:
	$(CC) -c $(SOURCES)
	$(CC) -o $(PROJECT) $(OBJECTS)
	./$(PROJECT)

clean:
	rm -rf *.o *.a a.out *.gch $(OUTFILENAME) ../.vscode

clang:
	clang-format -i $(SOURCES) $(HEADERS)

linter:
	clang-format -n $(SOURCES) $(HEADERS)

cppcheck:
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cpp *.h
