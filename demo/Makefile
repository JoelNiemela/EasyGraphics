WIN_LDLIBS = -static-libstdc++ -static-libgcc -static -lmingw32 -lglfw3 -lgdi32 -lglew32 -lopengl32

ifeq ($(target), win32)
PLATFORM = mingw32
CXX = i686-w64-mingw32-g++
PLATFORM_LDLIBS = $(WIN_LDLIBS)
PLATFORM_LDFLAGS = -L vendor/glew/lib/mingw32 -L vendor/glfw-3.3.7.bin.WIN32/lib-mingw-w64
TARGET = bin/$(PLATFORM)/demo.exe
else ifeq ($(target), win64)
PLATFORM = mingw64
CXX = x86_64-w64-mingw32-g++
PLATFORM_LDLIBS = $(WIN_LDLIBS)
PLATFORM_LDFLAGS = -L vendor/glew/lib/mingw64 -L vendor/glfw-3.3.7.bin.WIN64/lib-mingw-w64
TARGET = bin/$(PLATFORM)/demo.exe
else
PLATFORM = linux
PLATFORM_LDLIBS = -lglfw3 -lGLEW -lGL
PLATFORM_LDFLAGS = -L ../vendor/glew/lib -L ../vendor/glfw/build/src/
TARGET = bin/$(PLATFORM)/demo
endif

OBJDIR = obj/$(PLATFORM)

SRC = $(shell find src -type f -name '*.cpp' -printf '%P\n')
OBJ = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))
CPPFLAGS = -DGLEW_STATIC -I src -I ../include -I ../vendor/glew/include -I ../vendor/glfw/include -I ../vendor/glm -I ../vendor/imgui/include -I ../vendor/stb/include
CXXFLAGS = -Wall -std=c++20
LDFLAGS = -DGLEW_STATIC -L ../vendor/imgui/lib/$(PLATFORM) -L ../vendor/stb/lib/$(PLATFORM) -L ../lib/$(PLATFORM) $(PLATFORM_LDFLAGS)
LDLIBS = -lEasyGraphics -limgui -lstb $(PLATFORM_LDLIBS)

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(dir $@)
	$(CXX) -DGLEW_STATIC $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@

$(OBJDIR)/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -DGLEW_STATIC $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f -R $(OBJDIR)/*

clean_all:
	rm -f -R bin/*
	rm -f -R obj/*
