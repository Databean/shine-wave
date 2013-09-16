#ifndef IMAGE_H
#define IMAGE_H

#include <GL/gl.h>

#include <string>

GLuint loadImage(const std::string& path);

int getCurrentTextureWidth();

int getCurrentTextureHeight();


#endif