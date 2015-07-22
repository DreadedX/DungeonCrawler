#### PROJECT SETTINGS ####
# Compiler used
CXX ?= g++
# Program name
NAME = platformer
# Extension of source files used in the project
SRC_EXT = cpp
# Path to the source directory, relative to the makefile
SRC_PATH = src
# Space-separated pkg-config libraries used by this project
# General compiler flags
COMPILE_FLAGS = -std=c++14 -Wall -Wextra -g
# Add additional include paths
INCLUDES = -I ./include
# Destination directory, like a jail or mounted system
DESTDIR = /
# Used libraries
LIBS = -lGL -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lXcursor -lXinerama
#### END PROJECT SETTINGS ####

SOURCES = $(shell find $(SRC_PATH)/ -name '*.$(SRC_EXT)' -printf '%T@\t%p\n' \
		    | sort -k 1nr | cut -f2-)

all: $(NAME)

# release: $(NAME)-release

$(NAME): $(SOURCES)
	$(CXX) $(SOURCES) $(COMPILE_FLAGS) $(INCLUDES) $(LIBS) -o$(NAME)

# $(NAME)-release: $(SOURCES)
	# $(CXX) $(SOURCES) $(COMPILE_FLAGS) $(INCLUDES) $(LIBS) -o$(NAME)

clean:
	rm -f $(NAME)
