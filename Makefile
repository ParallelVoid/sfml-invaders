appname := invaders

# export LD_LIBRARY_PATH=/Users/tim/SFML-2.6.0/lib

CXX := clang++
CXXFLAGS := -std=c++17 -Wall -g -O0
INCLUDES := -I/Users/tim/SFML-2.6.0/include
LIBS := -L/Users/tim/SFML-2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC := $(shell find . -name "*.cpp")
OBJ  := $(patsubst %.cpp, %.o, $(SRC))

all: compile link

compile:
	@echo "\nCOMPILING\n"
	$(CXX) $(CXXFLAGS) -c $(SRC) $(INCLUDES)

link:
	@echo "\nLINKING...\n"
	$(CXX) $(OBJ)  -o $(appname) $(LIBS)

clean:
	rm -f main *.o
	rm -f invaders
