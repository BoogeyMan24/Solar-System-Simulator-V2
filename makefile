NAME=Solar\ System\ Simulator
BUILD_DIR = .
C_FILES = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
CPP_VERSION = -std=c++17

DEFINES:=
INCLUDES:= -Isrc -I../OpenGL/include -framework Cocoa -framework OpenGL -framework IOKit
LINKERS:= -L../OpenGL/lib -lglfw3 -lglew


all:
	clang++ $(CPP_VERSION) $(C_FILES) -o $(BUILD_DIR)/$(NAME) $(INCLUDES) $(LINKERS)
	$(BUILD_DIR)/$(NAME)

build:
	clang++ $(CPP_VERSION) $(C_FILES) -o $(BUILD_DIR)/$(NAME) $(INCLUDES) $(LINKERS)

run:
	$(BUILD_DIR)/$(NAME)