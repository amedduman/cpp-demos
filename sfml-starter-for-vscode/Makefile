SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = out
INCLUDE_PATHS = -I/opt/homebrew/Cellar/sfml/2.6.0/include
LIBRARY_PATHS = -L/opt/homebrew/Cellar/sfml/2.6.0/lib
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) $(COMPILER_FLAGS) $(SRC_FILES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)