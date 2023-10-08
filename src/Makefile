CC=g++
SOURCES=notes.cpp main.cpp
HEADERS=notes.h
CFLAGS=-Wall -Werror -Wextra -std=c++17

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	FILENAME=notes.app
else
	FILENAME=notes
endif

all: install

install:
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(SOURCES:.cpp=.o) -o $(FILENAME)
	./$(FILENAME)

clean:
	rm -rf *.o *.a a.out *.gch $(FILENAME) ../.vscode

clang:
	clang-format -i $(SOURCES) $(HEADERS)

linter:
	clang-format -n $(SOURCES) $(HEADERS)

cppcheck:
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cpp *.h
