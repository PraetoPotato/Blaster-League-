#include "cocos2d.h"
#include "Character.h"

using namespace cocos2d;

class Fighter :public Character //this is derived from the character class
{
public:
	Fighter() = default;
	Fighter(Vec2 position, std::string texturePath);

	//initialize all the frames for each animation
	void initRunAnim(std::vector<std::string> Frames,int NumOfFrames);
	void initJumpAnim(std::vector<std::string> Frames, int NumOfFrames);
	void initFallAnim(std::vector<std::string> Frames, int NumOfFrames);
	void initIdleAnim(std::vector<std::string> Frames, int NumOfFrames);


	//play the animtion
	void playRunAnim();
	void playJumpAnim();
	void playFallAnim();
	void playIdleAnim();

	//animations
	Animation *running;
	Animation *jump;
	Animation *fall;
	Animation *idle;

	Action action;

	//void addforce(Vec2 force);//adds force

	bool isRunning;
	bool isIdle;

	int JumpCounter;
	bool P1;
private:
	float temporaryInvincibility;//The amount of time left for invincibility after you died
	int lives;//the number of lives you have
	
};