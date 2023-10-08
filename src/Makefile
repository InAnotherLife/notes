CC=g++
SOURCES=notes.cpp main.cpp
HEADERS=notes.h
CFLAGS=-Wall -Werror -Wextra -std=c++17

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	PROJECT=notes.app
else
	PROJECT=notes
endif

all: install

install:
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(SOURCES:.cpp=.o) -o $(PROJECT)
	./$(PROJECT)

clean:
	rm -rf *.o *.a a.out *.gch $(OUTFILENAME) ../.vscode

clang:
	clang-format -i $(SOURCES) $(HEADERS)

linter:
	clang-format -n $(SOURCES) $(HEADERS)

cppcheck:
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cpp *.h
