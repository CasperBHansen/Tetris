#
# makefile
#
# declares the rules of building, testing, running and documenting the system.
#

PROJECT="Tetris"
CC=g++
LDFLAGS=-lSDL -pthread -std=c++11 -Wall
EXE=Tetris
SRC=*.cpp #*/*.cpp

run:
	./$(EXE)

docs:
	doxygen ../.doc

build:
	clear
	$(CC) $(SRC) $(LDFLAGS) -o $(EXE)

clean:
	rm -rf *.{o} .*.*.{swp,swo} .*.{swp,swo} $(EXE)

class:
	./.cpp_class.sh $(NAME) $(PROJECT)

.PHONY: clean class run

