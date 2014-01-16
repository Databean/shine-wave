#ifndef STATIC_LEVEL_H
#define STATIC_LEVEL_H

#include <vector>
#include <string>
#include <memory>
#include <utility>

#include "Spritesheet.h"

class StaticLevel {
private:
	std::unique_ptr<Spritesheet> spritesheet;
	std::vector<std::tuple<Sprite*, int, int>> sprites;
public:
	StaticLevel();
	
	void loadXMLFile(const std::string& filename);
	void draw() const;
};

#endif