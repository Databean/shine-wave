#include "StaticLevel.h"

#include <stdexcept>
#include <iostream>

#include "tinyxml2.h"

using std::cout;
using std::endl;

using std::string;
using std::vector;
using std::unique_ptr;
using std::tuple;

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

StaticLevel::StaticLevel() {
	
}

void StaticLevel::loadXMLFile(const string& file) {
	sprites.clear();
	
	XMLDocument doc;
	doc.LoadFile(file.c_str());
	XMLElement* level = doc.FirstChildElement("level");
	string spritesheetName(level->FirstChildElement("spritesheet")->GetText());
	if(spritesheetName.find(".xml") != string::npos) {
		spritesheet = Spritesheet::fromXMLFile(spritesheetName);
	} else if(spritesheetName.find(".txt") != string::npos) {
		spritesheet = Spritesheet::fromTextFile(spritesheetName);
	} else {
		throw std::runtime_error("Unknown spritesheet filetype");
	}
	
	XMLElement* elements = level->FirstChildElement("elements");
	for(XMLElement* spriteElement = elements->FirstChildElement(); spriteElement; spriteElement = spriteElement->NextSiblingElement()) {
		Sprite* sprite = spritesheet->getSprite(string(spriteElement->Attribute("name")));
		if(sprite) {
			for(XMLElement* instanceElement = spriteElement->FirstChildElement(); instanceElement; instanceElement = instanceElement->NextSiblingElement()) {
				string name(instanceElement->Name());
				if(name == "instance") {
					int x = instanceElement->IntAttribute("x");
					int y = instanceElement->IntAttribute("y");
					sprites.push_back(std::make_tuple(sprite, x, y));
				} else if(name == "strip") {
					int x = instanceElement->IntAttribute("x");
					int y = instanceElement->IntAttribute("y");
					int count = instanceElement->IntAttribute("count");
					for(int i = 0; i < count; i++) {
						sprites.push_back(std::make_tuple(sprite, x + (i * sprite->getWidth()), y));
					}
				}
			}
		}
	}
}

void StaticLevel::draw() const {
	for(const tuple<Sprite*, int, int>& spriteAndPos : sprites) {
		const Sprite* sprite = std::get<0>(spriteAndPos);
		const int& x = std::get<1>(spriteAndPos);
		const int& y = std::get<2>(spriteAndPos);
		sprite->draw(x, y);
	}
}