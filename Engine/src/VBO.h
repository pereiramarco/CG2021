#pragma once
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#endif

class VBO {
public:
	GLuint vertixes;
	int vertixCount;
	GLuint indexes;
	int indexCount;

    VBO();
};