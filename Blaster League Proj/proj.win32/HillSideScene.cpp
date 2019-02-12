#include "HillsideScene.h"
#include <iostream>
cocos2d::Scene * Hillside::createScene()
{

    auto scene = Scene::createWithPhysics();
	auto layer = Hillside::create();

	scene->addChild(layer);
	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();

	return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//Initialize everything
bool Hillside::init()
{
	//Ensure the parent init function was called first. If it wasn't, exit this one
	if (!Scene::init())
		return false;


	//Get the director from cocos so we can use it when needed
	director = Director::getInstance();

	//Init the sprites
	initSprites();

	//Init the mouse/ keyboard listeners
	initListeners();

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();

	//Let cocos know that the init function was successful
	return true;
}

//main game loop, updates everything
void Hillside::update(float deltatime)
{
	/*
	if (pressingA==true)
	{
	sprite->posit
	}
	*/
	if (KeyboardSpacePressed == true)
	{
		//insert what happens here
	}
}

void Hillside::initListeners()
{
	//Init the mouse listener
	initMouseListener();

	//Init the keyboard listener
	initKeyboardListener();
}

void Hillside::initSprites()
{
	//Initialize the Background 
	auto Sprite = Sprite::create("BackGrounds/Hillside Stage.png");
	if (Sprite == nullptr)
	{
		problemLoading("'BackGrounds/HillSide Stage.png'");
	}
	else
	{
		Sprite->setPosition(Vec2(2500, 1500));
		Sprite->setScale(0.4075);
		this->addChild(Sprite, 1);
	}

	//Initialize the Stage

	//Btw one this is invisible
	//This basically stops the player falling down
	Stage = new Character({ 2500,700 }, "Platforms/Platform.png");
	Stage->getSprite()->setPhysicsBody(PhysicsBody::createBox(Stage->getSprite()->getContentSize()));//Create a box Physics body
	Stage->getSprite()->getPhysicsBody()->setDynamic(false);
	this->addChild(Stage->getSprite(), 2);
	//this is the platform
	DisplayedStage= new Character({ 2500,575 }, "Platforms/Platform 2.png");
	this->addChild(DisplayedStage->getSprite(), 2);


	//Initialize the fighters
	Chandy = new Fighter({ 1500,2000 }, "Fighters/Chandy Sprite.png");
	Chandy->getSprite()->setPhysicsBody(PhysicsBody::createCircle((Chandy->getSprite()->getSpriteFrame()->getRectInPixels().size.height) * 0.5f * 0.65f));//Set Physics Body
	this->addChild(Chandy->getSprite(), 3);
}

void Hillside::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = [&](Event* event)
	{
		//Cast the event as a mouse event
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

		//Get the position of the mouse button press
		auto mouseClickPosition = mouseEvent->getLocationInView();
		mouseClickPosition.y += 540;

		//Init the message to be output in the message box
		std::stringstream message;

		//Get the mouse button from the event handler
		auto mouseButton = mouseEvent->getMouseButton();

		//Perform different logic depending on which button was pressed
		if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
			std::cout << "Left Mouse Button Pressed!" << std::endl;
		else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
			std::cout << "Right Mouse Button Pressed!" << std::endl;
	};


	//On Mouse Up
	mouseListener->onMouseUp = [&](Event* event)
	{
		//Cast the event as a mouse event
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

		//Get the position of the mouse button press
		auto mouseUpPosition = mouseEvent->getLocation();

		//Init the message to be output in the message box
		std::stringstream message;

		//Get the mouse button from the event handler
		auto mouseButton = mouseEvent->getMouseButton();

		//Perform different logic depending on which button was released
		if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
			std::cout << "Left Mouse Button Released!" << std::endl;
		else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
			std::cout << "Right Mouse Button Released!" << std::endl;
	};


	//On Mouse Move'
	mouseListener->onMouseMove = [&](cocos2d::Event* event)
	{
		//Cast the event as a mouse event
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

		//Get the position of the mouse from the event handler
		auto mouseEventPos = mouseEvent->getLocationInView();

		//Store the position into the mouse struct
		mousePosition = Vec2(mouseEventPos.x, 540 + mouseEventPos.y);

		//Output the position to the console
		//std::cout << this->mouse.position.x << ", " << this->mouse.position.y << std::endl;
	};


	//On Mouse Scroll
	mouseListener->onMouseScroll = [](cocos2d::Event* event)
	{
	};


	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithFixedPriority(mouseListener, 1);
}

void Hillside::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();


	//On Key Pressed
	keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{

		// If Statement for Spacebar Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			std::cout << "Space Bar Was Pressed!" << std::endl;
			KeyboardSpacePressed = true;

		}

		// If Statement for Key Up Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			std::cout << "Up Key Was Pressed!" << std::endl;
			KeyUpPressed = true;
		}

		// If Statement for Key Down Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			std::cout << "Down Key Was Pressed!" << std::endl;
			KeyDownPressed = true;
		}

		// If Statement for Key Right Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			std::cout << "Down Key Was Pressed!" << std::endl;
			KeyRightPressed = true;
		}

		// If Statement for Key Left Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			std::cout << "Left Key Was Pressed!" << std::endl;
			KeyLeftPressed = true;
		}

		// If Statement for a_lowercase Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			std::cout << "a Key Was Pressed!" << std::endl;
			KeyaPressed = true;
		}

		// If Statement for s_lowercase Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			std::cout << "s Key Was Pressed!" << std::endl;
			KeysPressed = true;
		}

		// If Statement for w_lowercase Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			std::cout << "w Key Was Pressed!" << std::endl;
			KeywPressed = true;
		}

		// If Statement for d_lowercase Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			std::cout << "d Key Was Pressed!" << std::endl;
			KeydPressed = true;
		}







	};


	//On Key Released
	keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			std::cout << "Space Bar Was Released!" << std::endl;
			KeyboardSpacePressed = false;

		}
		// If Statement for Key Up Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			std::cout << "Up Key Was Released!" << std::endl;
			KeyUpPressed = false;
		}

		// If Statement for Key Down Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			std::cout << "Down Key Was Released!" << std::endl;
			KeyDownPressed = false;
		}

		// If Statement for Key Right Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			std::cout << "Down Key Was Released!" << std::endl;
			KeyRightPressed = false;
		}

		// If Statement for Key Left Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			std::cout << "Left Key Was Released!" << std::endl;
			KeyLeftPressed = false;
		}

		// If Statement for a_lowercase Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			std::cout << "a Key Was Released!" << std::endl;
			KeyaPressed = false;
		}

		// If Statement for s_lowercase Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			std::cout << "s Key Was Released!" << std::endl;
			KeysPressed = false;
		}

		// If Statement for w_lowercase Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			std::cout << "w Key Was Released!" << std::endl;
			KeywPressed = false;
		}

		// If Statement for d_lowercase Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			std::cout << "d Key Was Released!" << std::endl;
			KeydPressed = false;
		}
	};


	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void Hillside::onExit()
{
	_eventDispatcher->removeAllEventListeners();
	Scene::onExit();
	std::cout << "Exited!" << std::endl;
}