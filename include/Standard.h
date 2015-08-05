#ifndef STANDARD_H
#define STANDARD_H

#ifndef DEBUG_MODE
#define DEBUG_MODE false
#endif
#ifndef DRAW_BOX
#define DRAWBOC false
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
#ifndef LEGACY
#define LEGACY false
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

// Other library includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

// Project includes
#include "Definitions.h"
#include "Game.h"
#include "Input.h"
#include "Script.h"
#include "Window.h"
#include "entities/Entity.h"
#include "gfx/Camera.h"
#include "gfx/Font.h"
#include "gfx/Render.h"
#include "gfx/ShaderLoader.h"
#include "gfx/TextureLoader.h"
#include "io/Reader.h"
#include "level/Level.h"
#include "level/Tile.h"
#include "util/Console.h"
#include "util/Log.h"
#include "util/String.h"

#endif
