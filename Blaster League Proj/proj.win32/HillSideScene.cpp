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
	Vec2 gravity(0,-980);   //980
	/*
	if (pressingA==true)
	{
	sprite->posit
	}
	*/


//-----------------------------------------movement for first fighter-------------------------------------------------


	if (KeywPressed == true && Chandy->position.y <= 1500)
	{
		
		if (Chandy->position.y <= 1500)
		{
			Chandy->position.y = 1501;
		}
		Chandy->position.y = Chandy->position.y + 0.01;
		Chandy->velocity.y=1000;
		
	}

	if (KeyboardSpacePressed == true)
	{
		ChandyCandy= new Character({ Chandy->position.x,Chandy->position.y }, "Fighters/PlaceHolder.png");
		ChandyCandy->IsBullet = true;


	

		
		ChandyCandy->velocity=(Vec2(500, 0));
		ChandyCandies.push_back(ChandyCandy);
		this->addChild(ChandyCandy->getSprite(),2);


		
		
		
	}






	if (KeydPressed == true)
	{
		Chandy->addForce(Vec2(500, 0));
		
	}
	if (KeyaPressed == true)
	{
		Chandy->addForce(Vec2(-500, 0));
		
	}
	
	if (KeysPressed == true)
	{
		Chandy->addForce(Vec2(0,-900));

	}
	if (KeydPressed == false)
	{
		//Drastically slow the movement until you come to a stop if you let go
		if (Chandy->acceleration.x != 0)
		{
			Chandy->acceleration.x -= 10000;
			
		}
		if (Chandy->velocity.x<=0&&KeyaPressed==false&& KeywPressed == true)
		{
			Chandy->velocity.x = 0;
			Chandy->acceleration.x = 0;
			/*Chandy->position.x = Chandy->getPositionX();*/
		}
		
	
	}
	if (KeyaPressed == false)
	{
		//Drastically slow the movement until you come to a stop if you let go
		if (Chandy->acceleration.x != 0)
		{
			Chandy->acceleration.x += 10000;

		}
		if (Chandy->velocity.x >= 0&& KeydPressed == false&&KeywPressed==true)
		{
			Chandy->velocity.x = 0;
			Chandy->acceleration.x = 0;
			Chandy->position.x = Chandy->getPositionX();
		}

	}
	if (KeyaPressed == false && KeydPressed == false && Chandy->position.y <= 1500)//stops movement for chandy if you let go of the a or d
	{
		Chandy->velocity.x = 0;
		Chandy->acceleration.x = 0;
	}



		if (KeyboardSpacePressed == false)
	{
	ChandyCandy->IsBullet == false;
	}
	

	//---------------------------------movement for the other fighter-------------------------------------------



	if (KeyUpPressed == true && Opponent->position.y <= 1500)
	{

		if (Opponent->position.y <= 1500)
		{
			Opponent->position.y = 1501;
		}
		Opponent->position.y = Opponent->position.y + 0.01;
		Opponent->velocity.y = 1000;

	}







/*	
	if (KeyboardSpacePressed == true)
	{
		ChandyCandy = new Character({ Chandy->position.x,Chandy->position.y }, "Fighters/PlaceHolder.png");
		ChandyCandy->IsBullet = true;
		ChandyCandy->velocity = (Vec2(10000, 0));
		ChandyCandies.push_back(ChandyCandy);
		this->addChild(ChandyCandy->getSprite(), 2);

	}
	


	*/


	if (KeyRightPressed == true)
	{
		Opponent->addForce(Vec2(500, 0));

	}
	if (KeyLeftPressed == true)
	{
		Opponent->addForce(Vec2(-500, 0));

	}

	if (KeyDownPressed == true)
	{
		Opponent->addForce(Vec2(0, -900));

	}
	if (KeyRightPressed == false)
	{
		//Drastically slow the movement until you come to a stop if you let go
		if (Opponent->acceleration.x != 0)
		{
			Opponent->acceleration.x -= 10000;

		}
		if (Opponent->velocity.x <= 0 && KeyLeftPressed == false && KeyUpPressed == true)
		{
			Opponent->velocity.x = 0;
			Opponent->acceleration.x = 0;
			/*Chandy->position.x = Chandy->getPositionX();*/
		}


	}
	if (KeyLeftPressed == false)
	{
		//Drastically slow the movement until you come to a stop if you let go
		if (Opponent->acceleration.x != 0)
		{
			Opponent->acceleration.x += 10000;

		}
		if (Opponent->velocity.x >= 0 && KeyRightPressed == false && KeyUpPressed == true)
		{
			Opponent->velocity.x = 0;
			Opponent->acceleration.x = 0;
			Opponent->position.x = Opponent->getPositionX();
		}

	}
	if (KeyLeftPressed == false && KeyRightPressed == false && Opponent->position.y <= 1500)//stops movement for chandy if you let go of the a or d
	{
		Opponent->velocity.x = 0;
		Opponent->acceleration.x = 0;
	}












	//-----------------------------gives the charcters gravity ----------------------------------------------
	

	Chandy->addForce(gravity);
	for (unsigned int i = 0; i < ChandyCandies.size(); i++)
	{
		//ChandyCandies[i]->addForce(gravity);
		ChandyCandies[i]->update(deltatime);


	}
	Chandy->update(deltatime);

	Opponent->addForce(gravity);
	Opponent->update(deltatime);
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

	//this is the platform
	DisplayedStage= new Character({ 2500,805 }, "Platforms/Platform 2.png");
	this->addChild(DisplayedStage->getSprite(), 2);


	//Initialize the fighters
	Chandy = new Fighter({ 1500,2000 }, "Fighters/Chandy Sprite.png");
	Chandy->IsBullet=false;
	this->addChild(Chandy->getSprite(), 3);

	Opponent = new Fighter({ 2500, 2000 }, "Fighters/Chandy Sprite2.png");
	Opponent->IsBullet = false;
	this->addChild(Opponent->getSprite(), 3);
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
			std::cout << "Right Key Was Pressed!" << std::endl;
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