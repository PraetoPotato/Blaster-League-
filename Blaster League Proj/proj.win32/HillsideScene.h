#pragma once
#include "cocos2d.h"
#include "Character.h"
#include "Fighter.h"

//Namespaces
using namespace cocos2d;

class Hillside : public cocos2d::Scene
{
public:
	//Engine Functions
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onExit();
	void update(float deltaTime);
	void loseLife();
	CREATE_FUNC(Hillside);

	void initListeners();
	void initSprites();
	void initHitBoxes();
	void initMouseListener();
	void initKeyboardListener();
private:
	//Engine
	Director* director;
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	Vec2 mousePosition;

	//Keyboard input booleans
	bool KeyboardSpacePressed;
	bool KeyUpPressed;
	bool KeyDownPressed;
	bool KeyLeftPressed;
	bool KeyRightPressed;
	bool KeyaPressed;
	bool KeywPressed;
	bool KeysPressed;
	bool KeydPressed;

	//Specific Conditions
	bool FirstShotfromPlayer1 = false;
	bool FirstShotfromPlayer2 = false;

	//Sprites 
	Sprite *BG;
	Character *Stage;
	Character *DisplayedStage;
	Character *ChandyLogo;
	Character *x;
	Character *Three;
	Character *Two;
	Character *One;
	Character *Zero;
	Fighter *Chandy;
	Fighter *Opponent;

	//Hitboxes
	Vec2 PositionRect;
	DrawNode *Node;


	//Projectiles
	Character *ChandyCandy;
	std::vector<Character*>ChandyCandies;
	
};