#pragma once
#include "cocos2d.h"
#include "Character.h"
#include "HillsideScene.h"
#include "TitleScreen.h"

//Namespaces
using namespace cocos2d;

class MapSelection : public cocos2d::Scene
{
public:
	//Engine Functions
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onExit();
	void update(float deltaTime);
	CREATE_FUNC(MapSelection);

	void initListeners();
	void initSprites();
	void initMouseListener();
	void initKeyboardListener();

	Character *StartButton;
	int Num;
private:
	//Engine
	Director* director;
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	Vec2 mousePosition;


	//Sprites 

	//Projectiles

};
