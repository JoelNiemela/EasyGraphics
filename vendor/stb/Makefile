LIB = stb

ifeq ($(target), win32)
CXX = i686-w64-mingw32-g++
AR = i686-w64-mingw32-ar
TARGET = lib/mingw32/$(LIB).lib
OBJDIR = obj/mingw32
else ifeq ($(target), win64)
CXX = x86_64-w64-mingw32-g++
AR = x86_64-w64-mingw32-ar
TARGET = lib/mingw64/$(LIB).lib
OBJDIR = obj/mingw64
else
TARGET = lib/linux/lib$(LIB).a
OBJDIR = obj/linux
endif

SRC = stb.c
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
CPPFLAGS = -I include
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
