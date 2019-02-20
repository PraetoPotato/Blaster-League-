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
	CREATE_FUNC(Hillside);

	void initListeners();
	void initSprites();
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

	//Sprites 
	Sprite *BG;
	Character *Stage;
	Character *DisplayedStage;
	Fighter *Chandy;
	Fighter *Opponent;

	//Projectiles
	Character *ChandyCandy;
	std::vector<Character*>ChandyCandies;
	
};