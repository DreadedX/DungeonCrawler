#ifndef STANDARD_H
#define STANDARD_H

#ifndef DEBUG_MODE
#define DEBUG_MODE false
#endif
#ifndef SCALE
#define SCALE 1
#endif
#ifndef TPS
#define TPS 60
#endif
#ifndef SWAP
#define SWAP 0
#endif
#ifndef PRINT_TO_TERMINAL
#define PRINT_TO_TERMINAL true
#endif

// Standard library includes
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdarg>
#include <memory>
#include <bitset>
#include <array>
#include <cassert>
#include <type_traits>
#include <thread>
#include <map>

#if DEBUG_MODE && __linux__
#include <proc/readproc.h>
#endif

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

// Zlib
#include <zlib.h>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

// Gorilla audio
#include "gorilla/ga.h"
#include "gorilla/gau.h"

// RapidJSON
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#if DEBUG_MODE
// Debug UI using imgui
#include "imgui/imgui.h"
#if not LEGACY
#include "imgui/imgui_impl_glfw_gl3.h"
#else
#include "imgui/imgui_impl_glfw.h"
#endif
#endif

#if DEBUG_MODE
// Leak checker
#include "leakage/debug_new.h"
#endif

// Project includes
#include "Definitions.h"

#include "util/Log.h"
#include "util/String.h"
#include "util/Math.h"

#include "entity/Entity.h"
#include "item/Item.h"
#include "entity/Components.h"

#include "Game.h"
#include "Input.h"
#include "Randomizer.h"
#include "Script.h"
#include "Window.h"

#include "audio/Audio.h"
#include "gfx/Camera.h"
#include "gfx/Render.h"
#include "gfx/ShaderLoader.h"
#include "gfx/TextureLoader.h"
#include "gui/Text.h"
#include "gui/TextBox.h"
#include "gui/Gui.h"
#include "io/Reader.h"
#include "level/LevelGenerator.h"
#include "level/BlueprintGenerator.h"
#include "level/Level.h"
#include "level/Tile.h"
#include "util/Command.h"
#include "util/Console.h"

#endif
