#include "cocos2d.h"
#include "Character.h"

using namespace cocos2d;

class Fighter :public Character //this is derived from the character class
{
public:
	Fighter() = default;
	Fighter(Vec2 position, std::string texturePath);

	void initRunAnim();
	void initJumpAnim();
	void initFallAnim();
	void initIdleAnim();

	void playRunAnim();
	void playJumpAnim();
	void playFallAnim();
	void playIdleAnim();

	Animation *running;
	Animation *jump;
	Animation *fall;
	Animation *idle;

	Action action;

	//void addforce(Vec2 force);//adds force


	int JumpCounter;
	bool P1;
private:
	float temporaryInvincibility;//The amount of time left for invincibility after you died
	int lives;//the number of lives you have
	
};