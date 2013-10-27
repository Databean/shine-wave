#include "PhysicsObject.h"

#include "Spritesheet.h"

PhysicsObject::PhysicsObject(const Sprite& sprite, float minX, float minY) : sprite(sprite), minX(minX), minY(minY) {
	
}

PhysicsObject::~PhysicsObject() {
	
}

bool PhysicsObject::containsPoint(float x, float y) const {
	return getMinX() < x && x < getMaxX() &&
		getMinY() < y && y < getMaxY();
}

bool PhysicsObject::boundingBoxCollides(const PhysicsObject& other) const {
	// http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
	return getMinX() < other.getMaxX() && getMaxX() > other.getMinX() &&
		getMinY() < other.getMaxY() && getMaxY() > other.getMinY();
}

const Sprite& PhysicsObject::getSprite() const {
	return sprite;
}

float PhysicsObject::getMinX() const {
	return minX;
}

float PhysicsObject::getMinY() const {
	return minY;
}

float PhysicsObject::getMaxX() const {
	return minX + sprite.getWidth();
}

float PhysicsObject::getMaxY() const {
	return minY + sprite.getHeight();
}
