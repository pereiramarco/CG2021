#include "../include/VBO.h"
#ifndef __APPLE__
#include <GL/glew.h>
#endif

VBO::VBO() {
	vertixCount=0;
	indexCount=0;
	glGenBuffers(1,&vertixes);
	glGenBuffers(1,&indexes);
	glGenBuffers(1,&normals);
	glGenBuffers(1,&texCoords);
}	

VBO::VBO(const VBO& vbo) {
	vertixCount=vbo.vertixCount;
	indexCount=vbo.indexCount;
	indexes=vbo.indexes;
	vertixes=vbo.vertixes;
	normals=vbo.normals;
	texCoords=vbo.texCoords;
}