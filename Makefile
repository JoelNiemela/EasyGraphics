LIB = EasyGraphics

DEFINES = -DGLEW_STATIC

ifeq ($(target), win32)
CXX = i686-w64-mingw32-g++
AR = i686-w64-mingw32-ar
DEFINES += -DWINDOWS
TARGET = lib/mingw32/$(LIB).lib
OBJDIR = obj/mingw32
else ifeq ($(target), win64)
CXX = x86_64-w64-mingw32-g++
AR = x86_64-w64-mingw32-ar
DEFINES += -DWINDOWS
TARGET = lib/mingw64/$(LIB).lib
OBJDIR = obj/mingw64
else
TARGET = lib/linux/lib$(LIB).a
OBJDIR = obj/linux
endif

SRC = $(shell find src -type f -name '*.cpp' -printf '%P\n')
OBJ = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))
INCLUDES = -I src -I vendor/glew/include -I vendor/glfw/include -I vendor/glm -I vendor/imgui/include -I vendor/stb/include
CPPFLAGS = $(DEFINES) $(INCLUDES)
CXXFLAGS = -Wall -std=c++20

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(dir $@)
	$(AR) rcs $@ $(OBJ)

$(OBJDIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -DGLEW_STATIC $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f -R $(OBJDIR)/*

clean_all:
	rm -f -R lib/*
	rm -f -R obj/*
