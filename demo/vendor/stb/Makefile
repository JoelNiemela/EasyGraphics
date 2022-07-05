SRC = stb.c
OBJ = $(patsubst %.c,%.o,$(SRC))
CPPFLAGS =
CXXFLAGS = -Wall

all: libstb.a

libstb.a: $(OBJ)
	ar rcs $@ $(OBJ)

%.o: %.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f libstb.a
