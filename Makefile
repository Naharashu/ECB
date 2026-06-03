CXX:=clang++
CXX_FLAGS:=-O2 -g -pipe -std=c++20 -Wall -march=x86-64 
CXX_FLAGS_DEBUG:=-O0 -g3 -pipe -std=c++20 -Wall -Wextra -fno-omit-frame-pointer -fsanitize=address
CXX_OBJECTS := build/ecb.o build/main.o 




.PHONY: all main debug clean install build


all: main


main: $(CXX_OBJECTS)
	$(CXX) $(CXX_FLAGS) $(CXX_OBJECTS) -o ecb

vpath %.cpp src src/include

debug: CXX_FLAGS=$(CXX_FLAGS_DEBUG)
debug: $(CXX_OBJECTS)
	$(CXX) $(CXX_FLAGS_DEBUG) $(CXX_OBJECTS) -o ecb


build/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@  

install:
	cp ecb ~/.local/bin/ecb

clean:
	rm -f ./ecb
	rm -f build/*.o