CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -Iinclude
SRC := $(wildcard src/*.cc)
OBJ := $(patsubst src/%.cc,build/%.o,$(SRC))
BIN := bin/mdp

.PHONY: all clean dirs

all: dirs $(BIN)

dirs:
	@mkdir -p build bin

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@

build/%.o: src/%.cc | dirs
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build bin results/*.csv results/*.txt