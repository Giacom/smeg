# Window users, please use a terminal with Unix commands.

BIN = bin
TARGET = $(BIN)/project-m

LIBS = -lSDL2

MKDIR = mkdir -p $(BIN)

INCLUDES = -I/usr/local/include -I./include
CXX = clang++
ifeq ($(OS),Windows_NT)
	CXX = g++ # Should be GCC compatible
endif
CXXFLAGS = -g -Wall -Werror -std=c++11

.PHONY: default all clean run

default: $(TARGET)
all: default run

OBJECTS = $(patsubst %.cpp, %.o, $(shell find $(SOURCEDIR) -name '*.cpp'))
HEADERS = $(wildcard includes/*.hpp)

%.o: %.c
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PRECIOUS:
	$(CXX) $(TARGET) $(OBJECT)

$(TARGET): $(OBJECTS)
	$(MKDIR)
	$(CXX) $(CFLAGS) $(OBJECTS) $(WIN_LIB_PATH) $(LIBS) $(INCLUDES) -o $@

clean:
	-rm -rf -- ./$(BIN)
	find . -type f -name '*.o' -delete
	find . -type f -name '*.d' -delete

run: $(TARGET)
	$(TARGET)