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
#include <string>
#include <cstdarg>

#if DEBUG_MODE && __linux__
#include <proc/readproc.h>
#endif

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

// OpenAL
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

// Zlib
#include <zlib.h>

// Debug UI using imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

// Project includes
#include "Definitions.h"
#include "Game.h"
#include "Input.h"
#include "Script.h"
#include "Window.h"
#include "audio/Audio.h"
#include "entities/Entity.h"
#include "gfx/Camera.h"
// #include "gfx/Font.h"
#include "gfx/Render.h"
#include "gfx/ShaderLoader.h"
#include "gfx/TextureLoader.h"
#include "io/Reader.h"
#include "level/Level.h"
#include "level/Tile.h"
#include "util/Command.h"
#include "util/Console.h"
#include "util/Log.h"
#include "util/String.h"

#endif
