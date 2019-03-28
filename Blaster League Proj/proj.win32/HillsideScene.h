#pragma once
#include "cocos2d.h"
#include "Character.h"
#include "Fighter.h"
#include "TitleScreen.h"
#include "Map Selection.h"

//Namespaces
using namespace cocos2d;

class Hillside : public cocos2d::Scene
{
public:
	//Engine Functions
	static cocos2d::Scene* createScene(int Number);
	virtual bool init();
	virtual void onExit();
	void update(float deltaTime);
	void loseLifeP1();
	void loseLifeP2();
	void grapple();
	void shoot(Fighter *theFighter);
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
	bool KeyqPressed;

	int StageNum;
	
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
	Character *Hook;
	Character *PivotPoint;
	Fighter *Chandy;
	Fighter *Opponent;

	Rect aabb;
	//Hitboxesddddddddddddddddddddddd
	DrawNode *Node;


	//Projectiles
	Character *ChandyCandy;
	std::vector<Character*>ChandyCandies;

	Character *OpponentCandy;
	std::vector<Character*>OpponentCandies;
	
};