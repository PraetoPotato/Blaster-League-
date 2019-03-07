#include "Character.h"
#include <iostream>
//void Character::kill(float delay)
//{
//	//delays by the provided amount, and then removes the bird.
//	sprite->runAction(Sequence::createWithTwoActions(DelayTime::create(delay), RemoveSelf::create()));
//}
Character::Character() {}
Character::Character(Vec2 position, std::string texturePath)
{
	load(position,texturePath);
}
void Character::load(Vec2 position, std::string texturePath)
{
	sprite = Sprite::create(texturePath); //Load the handle
	sprite->setPosition(position);
	sprite->setScale(0.25f); //Scale the bird since it loads in quite large 
	sprite->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the character is the anchor point
	//auto body = PhysicsBody::createCircle((sprite->getSpriteFrame()->getRectInPixels().size.height) * 0.5f * 0.65f); //This makes the hitbox a circle
	//auto body = PhysicsBody::createCircle(32.0f); //Use a circle since the bird is roughly circular
	std::cout << sprite->getSpriteFrame()->getRectInPixels().size.height * sprite->getScale() * 0.5f << std::endl;
	//sprite->setPhysicsBody(body); //Connect the physics body and the sprite
}

//Updates the positon of the character
void Character::update(float deltaTime)
{

	
	
	if (IsBullet == false)
	{
		acceleration.clamp(Vec2(-1000, -2000), Vec2(1000, 2000));//limit the acceleration
		velocity.clamp(Vec2(-2000, -2000), Vec2(2000, 2000));//limit the velocity
	}
	velocity += acceleration * deltaTime;
	position = sprite->getPosition();
	position += velocity * deltaTime;
	sprite->setPosition(position);
	
	


	
	
}
Sprite* Character::getSprite() {
	return sprite;
}

PhysicsBody* Character::getBody() {
	return sprite->getPhysicsBody();
}

void Character::setVelocity(Vec2 veloc)
{
	velocity = veloc;
}

void Character::setAcceleration(Vec2 accel)
{
	acceleration = Vec2(0, 0);
}

void Character::setPosition(Vec2 pos)
{
	position = Vec2(0, 0);
}

Vec2 Character::getPosition() {
	return sprite->getPosition();
}

float Character::getPositionX()
{
	return position.x;
}

float Character::getPositionY()
{
	return position.y;
}

void Character::addForce(Vec2 force)
{
	acceleration += force;
}

bool Character::IsCollidingWith(Character* otherCharacter)
{
	Rect Rect1 = getSprite()->getBoundingBox();
	Rect Rect2 = otherCharacter->getSprite()->getBoundingBox();
	if (Rect1.intersectsRect(Rect2)==true)
	{
		return true;
	}
	return false;
}

Character::~Character()
{
	//delete sprite;
	sprite = NULL;
}