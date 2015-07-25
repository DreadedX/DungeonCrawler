#### PROJECT SETTINGS ####
# Compiler used
CXX ?= g++
# Program name
NAME = gaff
# Extension of source files used in the project
SRC_EXT = cpp
# Path to the source directory, relative to the makefile
SRC_PATH = src
# General compiler flags
COMPILE_FLAGS = -std=c++14 -Wall -Wextra -g
# Add additional include paths
INCLUDES = -I ./include
# Destination directory, like a jail or mounted system
DESTDIR = /
# Used libraries
LIBS = libpng16
#### END PROJECT SETTINGS ####

SOURCES = $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' \
		    | sort -k 1nr | cut -f2-)

all: $(NAME)

$(NAME): $(SOURCES)
	$(CXX) $(SOURCES) $(COMPILE_FLAGS) $(shell pkg-config --libs --cflags $(LIBS)) $(INCLUDES) -o $(NAME)

execute:
	./$(NAME)

clean:
	rm -f $(NAME)
