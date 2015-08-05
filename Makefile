#### PROJECT SETTINGS ####
# Default build type
TYPE = debug

# Defaults for variables
PROGRAM_NAME = platformer
CXX = g++

DRAW_BOX = false
TPS = 60
SCALE = 2
SWAP = 0
LEGACY = false

# Variables based on build type
ifeq ($(TYPE),debug)
DEBUG = true
PRINT_TO_TERMINAL = false
COMPILE_FLAGS_EXTRA = -Wno-write-strings -Wno-unused-parameter -g
endif
ifeq ($(TYPE),release)
DEBUG = false
PRINT_TO_TERMINAL = true
COMPILE_FLAGS_EXTRA = -O3
endif

# Libraries
LIBS_EXTERN = libprocps glew glfw3 $(shell pkg-config --print-requires --print-requires-private glfw3)
#### END PROJECT SETTINGS ####
#
#
#
#
#
#
#
#

NAME = build/$(TYPE)/$(PROGRAM_NAME)
LIBS = $(shell pkg-config --libs --cflags $(LIBS_EXTERN))
DEFS = -DDEBUG_MODE=$(DEBUG) -DDRAW_BOX=$(DRAW_BOX) -DLEGACY=$(LEGACY) -DTPS=$(TPS) -DSCALE=$(SCALE) -DSWAP=$(SWAP) -DPRINT_TO_TERMINAL=$(PRINT_TO_TERMINAL)
COMPILE_FLAGS = -std=c++14 -Wall -Wextra $(COMPILE_FLAGS_EXTRA) $(DEFS)
INCLUDES = -I include -I libs/include
MAKEFLAGS = "-j $(shell grep -c ^processor /proc/cpuinfo)"

SOURCES = $(shell find src -name '*.cpp' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)
SOURCES_LIBS = $(shell find libs/src -name '*.cpp' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)

HEADERS = $(shell find include -name '*.h' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)
HEADERS_LIBS = $(shell find libs/include -name '*.h' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)

OBJECTS = $(subst .cpp,.o,$(subst src/,obj/, $(SOURCES)))
OBJECTS_LIBS = $(subst .cpp,.o,$(subst /src/,/obj/, $(SOURCES_LIBS)))

all: include/Standard.h.gch $(NAME)

$(NAME): $(OBJECTS_LIBS) $(OBJECTS) 
	g++ $(INCLUDES) $(LIBS) $(DEFS) $(COMPILE_FLAGS) -o $@ $^

$(OBJECTS) : obj/%.o : src/%.cpp ./Makefile include/Standard.h.gch
	g++ $(INCLUDES) $(LIBS) $(DEFS) $(COMPILE_FLAGS) -c -o $@ $<

$(OBJECTS_LIBS) : libs/obj/%.o : libs/src/%.cpp ./Makefile
	g++ $(INCLUDES) $(LIBS) $(DEFS) $(COMPILE_FLAGS) -c -o $@ $< -Wno-type-limits -Wno-missing-field-initializers

include/Standard.h.gch: $(HEADERS) $(HEADERS_LIBS) ./Makefile
	$(CXX) $(COMPILE_FLAGS) $(INCLUDES) include/Standard.h 

execute:
	cd sandbox; ./../$(NAME)

clean:
	rm -f build/debug/$(PROGRAM_NAME)
	rm -f build/release/$(PROGRAM_NAME)
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_LIBS)
