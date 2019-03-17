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
	void loseLifeP1();
	void loseLifeP2();

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
	bool KeyEnterPressed;
	bool KeyaPressed;
	bool KeywPressed;
	bool KeysPressed;
	bool KeydPressed;
	bool KeylPressed;


	//Specific Conditions
	bool FirstShotfromPlayer1 = false;
	bool FirstShotfromPlayer2 = false;

	bool Player1isFalling = false;
	bool Player2isFalling = false;

	//Sprites 
	Sprite *BG;
	Character *Stage;
	Character *DisplayedStage;
	Character *ChandyLogo;
	Character *OpponentLogo;
	Character *Platform1;
	Character *Platform2;
	Character *Platform3;
	Character *x;
	Character *Three;
	Character *Two;
	Character *One;
	Character *Zero;
	Character *x_;
	Character *Three_;
	Character *Two_;
	Character *One_;
	Character *Zero_;
	Fighter *Chandy;
	Fighter *Opponent;

	Rect aabb;
	//Hitboxes
	Vec2 PositionRect;
	DrawNode *Node;


	//Projectiles
	Character *ChandyCandy;
	std::vector<Character*>ChandyCandies;

	Character *OpponentCandy;
	std::vector<Character*>OpponentCandies;
	
};