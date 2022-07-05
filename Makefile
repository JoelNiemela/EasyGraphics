SRC = $(shell find src -type f -name '*.cpp' -printf '%P\n')
OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))
CPPFLAGS = -I src -I vendor
CXXFLAGS = -Wall -std=c++20
LDFLAGS = -L vendor/imgui -L vendor/stb
LDLIBS = -lglfw -lGLEW -lGL -limgui -lstb

all: libeg.a

libeg.a: $(OBJ)
	ar rcs $@ $(OBJ)

obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f libeg.a
	rm -f -R obj/*
