CC=g++
SOURCES=notes.cpp main.cpp
HEADERS=notes.h
CFLAGS=-Wall -Werror -Wextra -std=c++17
TESTNAME=tests

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	FILENAME=notes.app
	LDFLAGS=
	TESTFLAGS=-lgtest
else
	FILENAME=notes
	LDFLAGS=-lrt -lm -ldl
	TESTFLAGS=-lgtest -lpthread -lsubunit
endif

all: install

install:
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SOURCES)
	$(CC) $(SOURCES:.cpp=.o) -o $(FILENAME)
	./$(FILENAME)

uninstall:
	rm -f $(FILENAME)

clean:
	rm -f *.o *.a a.out *.gch $(TESTNAME)
	rm -rf ../.vscode

rebuild: clean install

tests:
	$(CC) $(CFLAGS) $(LDFLAGS) -c notes.cpp ../tests/tests.cpp
	$(CC) notes.o tests.o $(TESTFLAGS) -o $(TESTNAME)
	./$(TESTNAME)

clang-format:
	clang-format -i $(SOURCES) $(HEADERS)

linter:
	clang-format -n $(SOURCES) $(HEADERS)

cppcheck:
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cpp *.h
