#pragma once
#include "Globals.h"
#include "Graphic.h"

struct Cube : Graphic
{
	static const int NUM_FACES = 6;
	static const int NUM_TRIANGLES = NUM_FACES * 2;
	static const int NUM_VERTEXS = NUM_TRIANGLES * 3;

	//const glm::dvec3 a;
	//const glm::dvec3 b;
	//const glm::dvec3 c;
	//const glm::dvec3 d;
	//const glm::dvec3 e;
	//const glm::dvec3 f;
	//const glm::dvec3 g;
	//const glm::dvec3 h;
	//
	//const glm::dvec3 red;
	//const glm::dvec3 green;
	//const glm::dvec3 blue;
	//const glm::dvec3 yellow;
	//const glm::dvec3 white;
	//const glm::dvec3 black;

	Cube();
};

