#ifndef STANDARD_H
#define STANDARD_H

// Standard library includes
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/timeb.h>

// Other library includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

// Project includes
#include "Config.h"
#include "Definitions.h"
#include "Game.h"
#include "Input.h"
#include "Script.h"
#include "Window.h"
#include "entities/Entity.h"
#include "gfx/Camera.h"
#include "gfx/Render.h"
#include "gfx/ShaderLoader.h"
#include "gfx/TextureLoader.h"
#include "io/Reader.h"
#include "level/Level.h"
#include "level/Tile.h"
#include "util/Log.h"
#include "util/Tick.h"

#endif
