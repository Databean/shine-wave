#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <GL/gl.h>

#include <string>
#include <map>
#include <memory>

class Spritesheet;
class Sprite;

class Sprite {
private:
	Sprite(Sprite& other) : spritesheet(other.spritesheet) {}
	Sprite& operator=(const Sprite& other) { return *this; }
	
	Spritesheet& spritesheet;
	int x;
	int y;
	int width;
	int height;
	
public:
	Sprite(Spritesheet& spritesheet, int x, int y, int width, int height);
	virtual ~Sprite();
	
	Spritesheet& getSpritesheet();
	const Spritesheet& getSpritesheet() const;
	
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	
	void draw(int x, int y);
};

class Spritesheet {
private:
	Spritesheet(GLuint texture);
	Spritesheet(const Spritesheet&) {}
	Spritesheet& operator=(const Spritesheet&) { return *this; }
	
	void addSprite(const std::string& name, Sprite* toAdd);
	
	std::map<std::string, Sprite*> sprites;
	GLuint texture;
public:
	virtual ~Spritesheet();
	
	Sprite* getSprite(const std::string& string);
	GLuint getTexture() const;
	
	static std::unique_ptr<Spritesheet> fromTextFile(const std::string& path);
	static std::unique_ptr<Spritesheet> fromXMLFile(const std::string& path);
};


#endif