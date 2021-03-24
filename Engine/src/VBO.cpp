#include "VBO.h"
#include <GL/glew.h>

VBO::VBO() {
	vertixCount=0;
	indexCount=0;
	glGenBuffers(1,&vertixes);
	glGenBuffers(1,&indexes);
}	