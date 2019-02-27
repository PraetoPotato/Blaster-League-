#include "TitleScreen.h"
#include <iostream>
cocos2d::Scene * TitleScreen::createScene()
{

	auto scene = Scene::createWithPhysics();
	auto layer = TitleScreen::create();

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
bool TitleScreen::init()
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


//main game loop for this scene, updates everything
void TitleScreen::update(float deltatime)
{

}

void TitleScreen::initListeners()
{
	//Init the mouse listener
	initMouseListener();

	//Init the keyboard listener
	initKeyboardListener();
}

void TitleScreen::initSprites()
{
	//Initialize the Background 
	auto Sprite = Sprite::create("BackGrounds/Hillside Stage.png");
	if (Sprite == nullptr)
	{
		problemLoading("'BackGrounds/HillSide Stage.png'");//replace this image with the background for main menu
	}
	else
	{
		Sprite->setPosition(Vec2(2500, 1500));
		Sprite->setScale(0.4075);
		this->addChild(Sprite, 1);
	}

	StartButton = new Character({ 2500,805 }, "Menu/StartButton.png");
	this->addChild(StartButton->getSprite(), 2);


	
}

void TitleScreen::initMouseListener()
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

void TitleScreen::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//On Key Pressed
	keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			std::cout << "Space Bar Was Pressed!" << std::endl;

		}
	};

	//On Key Released
	keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			std::cout << "Space Bar Was Released!" << std::endl;

		}
		
	};



	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void TitleScreen::onExit()
{
	_eventDispatcher->removeAllEventListeners();
	Scene::onExit();
	std::cout << "Exited!" << std::endl;
}

