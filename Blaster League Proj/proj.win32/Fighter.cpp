#include "Fighter.h"

Fighter::Fighter(Vec2 position, std::string texturePath)
{
	load(position, texturePath);
	JumpCounter = 2;
	//initIdleAnim();
	//playIdleAnim();
}

void Fighter::initRunAnim(std::vector<std::string> Frames, int NumOfFrames)
{
	running = Animation::create();

	for (unsigned int i = 0; i < NumOfFrames; i++)
	{
		running->retain();
		running->addSpriteFrameWithFileName(Frames[i]);
	}


	running->setDelayPerUnit(0.1);
	
}

void Fighter::initJumpAnim(std::vector<std::string> Frames, int NumOfFrames)
{
	jump = Animation::create();
	
	for (unsigned int i = 0; i < NumOfFrames; i++)
	{
		jump->retain();
		jump->addSpriteFrameWithFileName(Frames[i]);
	}

	
	jump->setDelayPerUnit(0.1);
	
}

void Fighter::initFallAnim(std::vector<std::string> Frames, int NumOfFrames)
{
	fall = Animation::create();
	
	for (unsigned int i = 0; i < NumOfFrames; i++)
	{
		fall->retain();
		fall->addSpriteFrameWithFileName(Frames[i]);
	}

	
	fall->setDelayPerUnit(0.1);
	
}

void Fighter::initIdleAnim(std::vector<std::string> Frames, int NumOfFrames)
{
	//takes stuff from the initanimation from the hillsidescene
	idle = Animation::create();
	
	for (unsigned int i = 0; i < NumOfFrames; i++)
	{
		idle->retain();
		idle->addSpriteFrameWithFileName(Frames[i]);
	}

	
	idle->setDelayPerUnit(0.1);
	


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
