#include "../include/VBO.h"
#ifndef __APPLE__
#include <GL/glew.h>
#endif

VBO::VBO() {
	vertixCount=0;
	indexCount=0;
	glGenBuffers(1,&vertixes);
	glGenBuffers(1,&indexes);
}	