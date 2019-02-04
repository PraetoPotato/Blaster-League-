#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Character
{
public:
	Character();
	virtual ~Character();
	Character(Vec2 position, std::string spritePath);
	void update(float deltaTime);//get delta time so we don't have to keep calling elapsed time per seconds
	Sprite* getSprite();
	PhysicsBody* getBody();
	Vec2 getPosition();
	/*void kill(float delay = 0.0f);*/
	Vec2 position;
	Vec2 acceleration;
	Vec2 velocity;
protected:
	Sprite* sprite;

};