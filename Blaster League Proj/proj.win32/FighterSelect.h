#pragma once
#include "cocos2d.h"


//Namespaces
using namespace cocos2d;

class Pick : public cocos2d::Scene
{
public:
	//Engine Functions
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onExit();
	void update(float deltaTime);
	CREATE_FUNC(Pick);

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

};