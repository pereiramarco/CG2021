#pragma once
#include <GL/glew.h>

class VBO {
public:
	GLuint vertixes;
	int vertixCount;
	GLuint indexes;
	int indexCount;

    VBO();
};