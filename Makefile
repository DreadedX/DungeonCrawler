#### PROJECT SETTINGS ####
# Compiler used
CXX ?= g++
# Program name
NAME = platformer
# Extension of source files used in the project
SRC_EXT = cpp
# Path to the source directory, relative to the makefile
SRC_PATH = src
# Extra compiler settings
EXTRA = -Wno-write-strings #-Wno-deprecated
# General compiler flags
COMPILE_FLAGS = -std=c++14 -Wall -Wextra -g $(EXTRA)
# Add additional include paths
INCLUDES = -I ./include
# Destination directory, like a jail or mounted system
DESTDIR = /
# Used libraries
LIBS = python2 libpng16 glfw3 $(shell pkg-config --print-requires --print-requires-private glfw3)
#### END PROJECT SETTINGS ####

SOURCES = $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' \
		    | sort -k 1nr | cut -f2-)

all: $(NAME)

$(NAME): $(SOURCES)
	$(CXX) $(COMPILE_FLAGS) ./include/Standard.h 
	$(CXX) $(SOURCES) $(COMPILE_FLAGS) $(shell pkg-config --libs --cflags $(LIBS)) $(INCLUDES) -o $(NAME)

execute:
	./$(NAME)

clean:
	rm -f $(NAME)
