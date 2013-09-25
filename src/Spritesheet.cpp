#include "Spritesheet.h"

#include <GL/gl.h>

#include <stdexcept>
#include <fstream>
#include <cstddef>
#include <iostream>

#include "image.h"

#include "tinyxml2.h"

using std::string;
using std::unique_ptr;
using std::nullptr_t;

/**
 * Assuming (0,0) is the top left of both the screen and images.
 */
void drawSprite(const Sprite& sprite, int x, int y) {
	
	std::cout << "drawing" << std::endl;
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, sprite.getSpritesheet().getTexture());
	
	//Casting these to float ahead of time for readability.
	
	float spriteSheetX = sprite.getX();
	float spriteSheetY = sprite.getY();
	float spriteWidth = sprite.getWidth();
	float spriteHeight = sprite.getHeight();
	
	float textureWidth = getCurrentTextureWidth();
	float textureHeight = getCurrentTextureHeight();
	
	//Trick to not have to divide by textureWidth and textureHeight everywhere.
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glScaled(1.0 / textureWidth, 1.0 / textureHeight, 1);
	glTranslatef(spriteSheetX, spriteSheetY, 0);
	
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);
		
		glTexCoord2f(spriteWidth, 0);
		glVertex2f(spriteWidth, 0);
		
		glTexCoord2f(spriteWidth, spriteHeight);
		glVertex2f(spriteWidth, spriteHeight);
		
		glTexCoord2f(0, spriteHeight);
		glVertex2f(0, spriteHeight);
	}
	glEnd();
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

Sprite::Sprite(Spritesheet& spritesheet, int x, int y, int width, int height) :
	spritesheet(spritesheet), x(x), y(y), width(width), height(height) {
	
}

Sprite::~Sprite() {
	
}

Spritesheet& Sprite::getSpritesheet() {
	return spritesheet;
}

const Spritesheet& Sprite::getSpritesheet() const {
	return spritesheet;
}

/**
 * Returns the x position of the sprite on the page, in pixels.
 */
int Sprite::getX() const {
	return x;
}

/**
 * Returns the y position of the sprite on the page, in pixels.
 */
int Sprite::getY() const {
	return y;
}

/**
 * Returns the width of the sprite, in pixels.
 */
int Sprite::getWidth() const {
	return width;
}

/**
 * Returns the height of the sprite, in pixels.
 */
int Sprite::getHeight() const {
	return height;
}

/**
 * This constructor is private. Most of the initialization happens in the named
 * constructors fromTextFile and fromXMLFile.
 */
Spritesheet::Spritesheet(GLuint texture) : texture(texture) {
	
}

/**
 * Deletes the sprites stored in the spritesheet. The sprite objects are all allocated
 * in the named constructors fromTextFile and fromXMLFile.
 */
Spritesheet::~Spritesheet() {
	for(auto it = sprites.begin(); it != sprites.end(); it++) {
		delete it->second;
	}
}

/**
 * Every spritesheet has an image and some sprite boundaries. This returns the index for the stored
 * OpenGL texture.
 */
GLuint Spritesheet::getTexture() const {
	return texture;
}

/**
 * Returns a pointer to the sprite with the given name if it exists, and otherwise returns NULL.
 */
Sprite* Spritesheet::getSprite(const string& name) {
	if(sprites.count(name) > 0) {
		return sprites[name];
	} else {
		return NULL;
	}
}

/**
 * Internal function to add a sprite to the map of sprites.
 */
void Spritesheet::addSprite(const string& name, Sprite* s) {
	if(sprites.count(name) > 0) {
		throw std::runtime_error("A sprite with the name \""+name+"\" already exists in this sheet.");
	} else {
		sprites[name] = s;
	}
}

/**
 * Reads a set of sprites with names and bounding boxes on images from a text file.
 * The file has the format:
 * 
 * image_path
 * sprite_name x y w h
 * sprite_name x y w h
 * ...
 */
unique_ptr<Spritesheet> Spritesheet::fromTextFile(const string& fileName) {
	std::fstream fileStream(fileName);
	if(!fileStream) {
		return unique_ptr<Spritesheet>();
	}
	
	string imageName;
	fileStream >> imageName;
	
	GLuint texture = loadImage(imageName);
	
	unique_ptr<Spritesheet> sheet(new Spritesheet(texture));
	
	while(!fileStream.eof()) {
		string spriteName, equals;
		int x, y, width, height;
		
		fileStream >> spriteName >> equals >> x >> y >> width >> height;
		// The eof doesn't get triggered until after it tries to read the final newline.
		if(spriteName != "") {
			std::cout << spriteName << " = " << x << " " << y << " " << width << " " << height << std::endl;
			sheet->addSprite(spriteName, new Sprite(*sheet, x, y, width, height));
		}
	}
	
	return sheet;
}

