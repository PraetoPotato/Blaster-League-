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
	auto body = PhysicsBody::createCircle((sprite->getSpriteFrame()->getRectInPixels().size.height) * 0.5f * 0.65f); //This makes the hitbox a circle
	//auto body = PhysicsBody::createCircle(32.0f); //Use a circle since the bird is roughly circular
	std::cout << sprite->getSpriteFrame()->getRectInPixels().size.height * sprite->getScale() * 0.5f << std::endl;
	body->setContactTestBitmask(0xFFFFFFFF);
	//sprite->setPhysicsBody(body); //Connect the physics body and the sprite
}

//Updates the positon of the character
void Character::update(float deltaTime)
{
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

Vec2 Character::getPosition() {
	return sprite->getPosition();
}

void Character::addForce(Vec2 force)
{
	acceleration += force;
}

Character::~Character()
{
	//delete sprite;
	sprite = NULL;
}