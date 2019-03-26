#include "Fighter.h"

Fighter::Fighter(Vec2 position, std::string texturePath)
{
	load(position, texturePath);
	JumpCounter = 2;
	initIdleAnim();
	playIdleAnim();
}

void Fighter::initIdleAnim()
{
	idle = Animation::create();
	
	
	
	
}

void Fighter::playIdleAnim()
{

	getSprite()->runAction(Animate::create(idle));
}
