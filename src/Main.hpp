#pragma once
#include <GL/glew.h>
#include "../include/GLFW/glfw3.h"

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include "VAOBuilder.hpp"
#include "ShaderBuilder.hpp"
#include "Camera.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "Piece.hpp"
#include "Arm.hpp"
#include "Grid.hpp"
#include "Settings.hpp"

bool keys[1024];
bool shift;
bool ctrl;
bool alt;
bool super;

GLfloat deltaTime     = 0.f;
GLfloat timeLastFrame = 0.f;
GLfloat rotateTimer   = rotateTimerMax;

GLfloat distance   = initDistance;
GLfloat orbitAngle = initOrbitAngle;

Piece* piece = NULL;
Board* board = NULL;
Arm*   arm   = NULL;
Grid*  grid  = NULL;
