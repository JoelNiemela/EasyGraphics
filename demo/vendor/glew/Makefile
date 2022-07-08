ifeq ($(target), win32)
CXX = i686-w64-mingw32-g++
AR = i686-w64-mingw32-ar
TARGET = lib/mingw32/glew32.lib
OBJDIR = obj/mingw32
else ifeq ($(target), win64)
CXX = x86_64-w64-mingw32-g++
AR = x86_64-w64-mingw32-ar
TARGET = lib/mingw64/glew32.lib
OBJDIR = obj/mingw64
else
TARGET = lib/linux/libglew.a
OBJDIR = obj/linux
endif

SRC = glew.c
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
CPPFLAGS = -D GLEW_STATIC -I include
CXXFLAGS = -Wall

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(dir $@)
	$(AR) rcs $@ $(OBJ)

$(OBJDIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f -R $(OBJDIR)/*

clean_all:
	rm -f -R lib/*
	rm -f -R obj/*
