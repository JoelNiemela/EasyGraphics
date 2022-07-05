SRC = $(notdir $(wildcard *.cpp))
OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))
CPPFLAGS =
CXXFLAGS = -Wall

all: libimgui.a

libimgui.a: $(OBJ)
	ar rcs $@ $(OBJ)

obj/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm obj/*.o
	rm libimgui.a
