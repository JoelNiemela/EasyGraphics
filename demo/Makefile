SRC = $(shell find src -type f -name '*.cpp' -printf '%P\n')
OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))
CPPFLAGS = -I src -I ../src -I ../vendor
CXXFLAGS = -Wall -std=c++20
LDFLAGS = -L ../vendor/imgui -L ../vendor/stb -L ..
LDLIBS = -leg -lglfw -lGLEW -lGL -limgui -lstb

all: demo

demo: $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@

obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f demo
	rm -f -R obj/*
