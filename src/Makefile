CC=g++
SOURCES=notes.cpp main.cpp
HEADERS=notes.h
CFLAGS=-Wall -Werror -Wextra -std=c++17

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	FILENAME=notes.app
	LDFLAGS=
else
	FILENAME=notes
	LDFLAGS=-lrt -lm -ldl
endif

all: install

install:
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SOURCES)
	$(CC) $(SOURCES:.cpp=.o) -o $(FILENAME)
	./$(FILENAME)

uninstall:
	rm -f $(FILENAME)

clean:
	rm -f *.o *.a a.out *.gch
	rm -rf ../.vscode

rebuild: clean install

clang-format:
	clang-format -i $(SOURCES) $(HEADERS)

linter:
	clang-format -n $(SOURCES) $(HEADERS)

cppcheck:
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cpp *.h
