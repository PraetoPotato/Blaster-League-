#include "Fighter.h"

Fighter::Fighter(Vec2 position, std::string texturePath)
{
	load(position, texturePath);
	JumpCounter = 2;
	//initIdleAnim();
	//playIdleAnim();
}

void Fighter::initRunAnim(std::string * Frames, int NumOfFrames)
{
	running = Animation::create();
}

void Fighter::initJumpAnim(std::string * Frames, int NumOfFrames)
{
	jump = Animation::create();
}

void Fighter::initFallAnim(std::string * Frames, int NumOfFrames)
{
	fall = Animation::create();
}

void Fighter::initIdleAnim(std::string* Frames, int NumOfFrames)
{
	//takes stuff from the initanimation from the hillsidescene
	idle = Animation::create();

	//btw these commented code work, you just have to modify it

	/*idle->addSpriteFrameWithFileName("Fighters/Chandy Sprite.png");
	idle->addSpriteFrameWithFileName("Fighters/Chandy Sprite2.png");
	idle->addSpriteFrameWithFileName("Fighters/PlaceHolder.png");
	idle->retain();
	idle->setDelayPerUnit(0.1);
	idle->setLoops(100);*/
	
}

void Fighter::playRunAnim()
{
	getSprite()->runAction(Animate::create(running));
}

void Fighter::playJumpAnim()
{
	getSprite()->runAction(Animate::create(jump));
}

void Fighter::playFallAnim()
{
	getSprite()->runAction(Animate::create(fall));
}

void Fighter::playIdleAnim()
{

	getSprite()->runAction(Animate::create(idle));

}
