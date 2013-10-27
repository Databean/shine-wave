#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "Spritesheet.h"

/**
 * An object that can collide with other objects in the game. All of these have a sprite for now,
 * this class can be split up in the future if there need to be PhysicsObjects without sprites.
 * The x and y coordinates are of the minimum x and minimum y of all the points contained in the
 * object. The sprite should have a width and height.
 */
class PhysicsObject {
private:
	const Sprite& sprite;
	
	float minX;
	float minY;
public:
	PhysicsObject(const Sprite& sprite, float minX, float minY);
	virtual ~PhysicsObject();
	
	bool containsPoint(float x, float y) const;
	bool boundingBoxCollides(const PhysicsObject& other) const;
	
	const Sprite& getSprite() const;
	float getMinX() const;
	float getMinY() const;
	float getMaxX() const;
	float getMaxY() const;
};

#endif