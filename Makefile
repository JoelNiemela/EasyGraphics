SRC = $(shell find src -type f -name '*.cpp' -printf '%P\n')
OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))
CPPFLAGS = -I src -I vendor
CXXFLAGS = -Wall -std=c++20

all: libEasyGraphics.a

libEasyGraphics.a: $(OBJ)
	ar rcs $@ $(OBJ)

obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f libEasyGraphics.a
	rm -f -R obj/*
