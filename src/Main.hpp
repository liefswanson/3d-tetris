#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include "VAOBuilder.hpp"
#include "ShaderBuilder.hpp"
#include "Camera.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "Settings.hpp"

bool keys[1024];

GLfloat deltaTime     = 0.f;
GLfloat timeLastFrame = 0.f;
GLfloat timeThisFrame = 0.f;

