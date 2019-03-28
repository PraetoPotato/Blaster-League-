#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Character
{
public:
	Character();
	virtual ~Character();
	Character(Vec2 position, std::string spritePath);
	void load(Vec2 position, std::string spritePath);//same as the character constructor,this is used so that constructor can be called by derived functions
	void update(float deltaTime);//get delta time so we don't have to keep calling elapsed time per seconds
	Sprite* getSprite();
	PhysicsBody* getBody();
	void setVelocity(Vec2 veloc);
	void setAcceleration(Vec2 accel);
	void setPosition(Vec2 pos);
	Vec2 getPosition();
	float getOverlapX(Character* otherCharacter);
	float getOverlapY(Character* otherCharacter);
	float getPositionX();
	float getPositionY();
	void addForce(Vec2 force);
	bool IsCollidingWith(Character* otherCharacter);
	float findAngle(Character* otherChatracter);
	float FindLength(Character* otherCharacter);

	float length;
	float theta;
	Vec2 origin;
	bool isHit;
	bool isGrappling;
	Vec2 position;
	Vec2 acceleration;
	Vec2 velocity;
	bool IsBullet;
	bool fromOtherCharacter;
	bool isFalling;
	float hitStunTimer;
	float coolDowntimer2;
	float coolDowntimer;//cool down timer
	float MinX, MaxX, MinY, MaxY,MidX;
	
protected:
	Sprite* sprite;

};