# Default values
TYPE = debug
CXX = g++

# Load project settings
CONFIG = default
include make/$(CONFIG)

# Set compile flags for debug build
ifeq ($(TYPE),debug)
COMPILE_FLAGS += -g -DDEBUG_MODE=true
endif

# Set compile flags for release build
ifeq ($(TYPE),release)
COMPILE_FLAGS += -O3
endif

NAME = bin/$(TYPE)/$(PROGRAM_NAME)
LIBS = $(shell pkg-config --libs --cflags $(LIBS_EXTERN))
COMPILE_FLAGS += -Wno-write-strings -std=c++14 -Wall -Wextra $(COMPILE_FLAGS_EXTRA) $(DEFS)
# TODO: Make this automated
INCLUDES = -I include -I libs/include -I libs/include/imgui -I libs/include/leakage -I libs/include/rapidjson
MAKEFLAGS = "-j $(shell grep -c ^processor /proc/cpuinfo)"

SOURCES = $(shell find src -name '*.cpp' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)
SOURCES_LIBS = $(shell find libs/src -name '*.cpp' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)

HEADERS = $(shell find include -name '*.h' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)
HEADERS_LIBS = $(shell find libs/include -name '*.h' -printf '%T@\t%p\n' | sort -k 1nr | cut -f2-)

OBJECTS = $(subst .cpp,.o,$(subst src/,obj/$(TYPE)/, $(SOURCES)))
OBJECTS_LIBS = $(subst .cpp,.o,$(subst /src/,/obj/$(TYPE)/, $(SOURCES_LIBS)))

all: include/Standard.h.gch $(NAME) build/gaff/files.json

$(NAME): $(OBJECTS_LIBS) $(OBJECTS) 
	g++ $(INCLUDES) $(LIBS) $(DEFS) $(COMPILE_FLAGS) -o $@ $^

$(OBJECTS) : obj/$(TYPE)/%.o : src/%.cpp ./Makefile include/Standard.h.gch
	g++ $(INCLUDES) $(LIBS) $(DEFS) $(COMPILE_FLAGS) -c -o $@ $<

$(OBJECTS_LIBS) : libs/obj/$(TYPE)/%.o : libs/src/%.cpp ./Makefile
	g++ $(INCLUDES) $(LIBS) $(DEFS) $(COMPILE_FLAGS) -c -o $@ $< -Wno-type-limits -Wno-missing-field-initializers

include/Standard.h.gch: $(HEADERS) $(HEADERS_LIBS) ./Makefile
	$(CXX) $(COMPILE_FLAGS) $(INCLUDES) include/Standard.h 

run: build/gaff/files.json
	cd sandbox; ./../$(NAME)

debug: build/gaff/files.json
	cd sandbox; gdb ../$(NAME) -ex run -ex bt -ex quit --silent

valgrind: build/gaff/files.json
	cd sandbox; valgrind ./../$(NAME) -ex run -ex bt -ex quit --silent

build/gaff/files.json: $(shell find build/gaff/in) build/gaff/files-pre.js ./Makefile
	cd build/gaff; node files-pre.js && ./gaff
	cp build/gaff/out.gaff sandbox/out.gaff

clean:
	rm -f bin/debug/$(PROGRAM_NAME)
	rm -f bin/release/$(PROGRAM_NAME)
	rm -f build/gaff/files.json
	rm -f include/Standard.h.gch
	rm -f $(subst .cpp,.o,$(subst src/,obj/debug/, $(SOURCES)))
	rm -f $(subst .cpp,.o,$(subst src/,obj/release/, $(SOURCES)))
	rm -f $(OBJECTS_LIBS)
