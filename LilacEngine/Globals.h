#pragma once

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 )

#include <windows.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <shellapi.h>
#include <set>
#include <memory>
#include <vector>
#include <array>
#include <filesystem>
#include <span>
#include <list>
#include <utility>
#include <algorithm>
#include <gl/glew.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <IL/il.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI


typedef unsigned int uint;
using namespace std;
using namespace chrono;
namespace fs = std::filesystem;
using namespace std::chrono_literals;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Lilac Engine"

// Vectors
using vec2d = glm::dvec2;
using vec3d = glm::dvec3;
using vec4d = glm::dvec4;
using mat4d = glm::dmat4;

using vec2f = glm::vec2;
using vec3f = glm::vec3;
using vec4f = glm::vec4;