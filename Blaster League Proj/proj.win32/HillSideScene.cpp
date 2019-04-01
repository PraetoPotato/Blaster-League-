#include "HillsideScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

int Num;
int Num2=1;
int p1Jumps = 2;
int P1Lives = 3;
int P2Lives = 3;
// Gun hit noise
using namespace CocosDenshion;



cocos2d::Scene * Hillside::createScene(int Number)
{
	Num = Number;

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
	
	auto audio = SimpleAudioEngine::getInstance();

	// Set the background music and continuosly play it.
	audio->playBackgroundMusic("Music/BackgroundMusic.mp3", true);

	auto audio4 = SimpleAudioEngine::getInstance();
	// Set the lost life sound effect
	audio4->playEffect("Music/321Fight.mp3", false);

	//auto audio2 = SimpleAudioEngine::getInstance();
	// Set the background music and continuosly play it.
	//audio2->playEffect("Music/123Fight.mp3", true, 1.0f, 1.0f, 1.0f);



	//Ensure the parent init function was called first. If it wasn't, exit this one
	if (!Scene::init())
		return false;


	//Get the director from cocos so we can use it when needed
	director = Director::getInstance();

	//Init the sprites
	initSprites();

	//init hitboxes
	initHitBoxes();
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
	/*if (P1Lives < 0)
	{


		auto gameplayScene = WinScreen::createScene();
		director->replaceScene(gameplayScene);

	}

	if (P2Lives < 0)
	{


		auto gameplayScene = WinScreen::createScene();
		director->replaceScene(gameplayScene);

	}
*/
	Vec2 gravity(0,-1700);   
//-----------------------------------------------------------------------
	
	if (Chandy->acceleration.y >= 0)
	{
		Player1isFalling = false;
	}

	if (Chandy->acceleration.y < 0)
	{
		Player1isFalling = true;
	}
		

//-----------------------------------------updating cool down timer------------------
	
	Chandy->coolDowntimer -= deltatime;
	Opponent->coolDowntimer -= deltatime;
	Opponent->coolDowntimer2 -= deltatime;

	if (Opponent->coolDowntimer <= 0)
	{
		Opponent->isHit = false;
	}

	if (Opponent->coolDowntimer2 <= 0)
	{
		Chandy->isHit = false;
	}
//------------------------------------------Check for Collisions--------------------------------------
	if (Chandy->getSprite()->getBoundingBox().getMidY() < DisplayedStage->getSprite()->getBoundingBox().getMaxY())
	{
		if (Chandy->getSprite()->getBoundingBox().getMaxX() <= DisplayedStage->getSprite()->getBoundingBox().getMidX())
		{
			if (Chandy->IsCollidingWith(DisplayedStage) == true)
			{
				Chandy->velocity.x = -1000;
			}
			
		}
		if (Chandy->getSprite()->getBoundingBox().getMinX() >= DisplayedStage->getSprite()->getBoundingBox().getMidX())
		{
			if (Chandy->IsCollidingWith(DisplayedStage) == true)
			{
				Chandy->velocity.x = 1000;
			}
			
		}
	}
	if (Chandy->IsCollidingWith(DisplayedStage) == true)
	{
		Chandy->velocity.y = 0;
		Chandy->acceleration.y = 1700;
		Chandy->JumpCounter = 2;

	}


	if (Opponent->getSprite()->getBoundingBox().getMidY() < DisplayedStage->getSprite()->getBoundingBox().getMaxY())
		
	{
			if (Opponent->getSprite()->getBoundingBox().getMaxX() <= DisplayedStage->getSprite()->getBoundingBox().getMidX())
			{

				if (Opponent->IsCollidingWith(DisplayedStage) == true&&Opponent->isHit==false)
				{
					Opponent->velocity.x = -1000;
					Opponent->position.x = DisplayedStage->getSprite()->getBoundingBox().getMinX()-1;
				}

			}
			if (Opponent->getSprite()->getBoundingBox().getMinX() >= DisplayedStage->getSprite()->getBoundingBox().getMidX())
			{
				if (Opponent->IsCollidingWith(DisplayedStage) == true)
				{
					Opponent->velocity.x = 1000;
				}

			}
		

		
	}

	if (Opponent->IsCollidingWith(DisplayedStage) == true)
	{
		Opponent->velocity.y = 0;
		Opponent->acceleration.y = 1700;
		Opponent->JumpCounter = 2;


	}

//-------------------------------------Conditions for Idle Animation-----------------------------------------------------


	if (Chandy->IsCollidingWith(DisplayedStage)==true)
	{
		Chandy->playRunAnim();
		
		
	}
	if (Chandy->velocity.x!=0&&Chandy->IsCollidingWith(DisplayedStage) == true&&KeyaPressed==true|| Chandy->velocity.x != 0 && Chandy->IsCollidingWith(DisplayedStage) == true && KeydPressed == true)
	{
		Chandy->playIdleAnim();
		
	}

	if (Chandy->velocity.y>0)
	{
		Chandy->playJumpAnim();
	}

	if (Chandy->IsCollidingWith(DisplayedStage) == false&& Chandy->velocity.y < 0)
	{
		Chandy->playFallAnim();
	}



	if (Opponent->IsCollidingWith(DisplayedStage) == true)
	{
		Opponent->playIdleAnim();


	}
	if (Opponent->velocity.x != 0 && Opponent->IsCollidingWith(DisplayedStage) == true && KeyLeftPressed == true || Opponent->velocity.x != 0 && Opponent->IsCollidingWith(DisplayedStage) == true && KeyRightPressed == true)
	{
		
		Opponent->playRunAnim();

	}

	if (Opponent->velocity.y > 0)
	{
		Opponent->playJumpAnim();
	}

	/*if (Opponent->velocity.y < 0)
	{
		Opponent->playFallAnim();
	}*/
	
	
		



	
//----------------------------------------------Bullets------------------------------
	
	//add gravity to each bullet
	for (int i = 0; i < ChandyCandies.size(); i++)
	{
		ChandyCandies[i]->addForce(gravity);
	}

	for (int i = 0; i < OpponentCandies.size(); i++)
	{
		OpponentCandies[i]->addForce(gravity);

	}


	for (int i = 0; i < ChandyCandies.size(); i++)
	{

		if (ChandyCandies[i]->IsCollidingWith(Opponent) == true)
		{
			
			if (Opponent->position.x < Chandy->position.x)
			{
				Opponent->isHit = true;
				Opponent->coolDowntimer = 0.3;
				Opponent->velocity = (Vec2(-1000, 0));
				ChandyCandies[i]->getSprite()->removeFromParent();
				delete ChandyCandies[i];
				ChandyCandies.erase(ChandyCandies.begin() + i);
				i--;
			}
			if (Opponent->position.x > Chandy->position.x)
			{
				Opponent->isHit = true;
				Opponent->coolDowntimer = 0.3;
				Opponent->velocity = (Vec2(1000, 0));
				ChandyCandies[i]->getSprite()->removeFromParent();
				delete ChandyCandies[i];
				ChandyCandies.erase(ChandyCandies.begin() + i);
				i--;
			}

		}

	}

	for (int i = 0; i < ChandyCandies.size(); i++)
	{

		if (ChandyCandies[i]->position.y<=0)
		{
			ChandyCandies[i]->getSprite()->removeFromParent();
			delete ChandyCandies[i];
			ChandyCandies.erase(ChandyCandies.begin() + i);
			i--;

		}

	}

	for (int i = 0; i < OpponentCandies.size(); i++)
	{

		if (OpponentCandies[i]->IsCollidingWith(Chandy) == true)
		{
			if (Opponent->position.x > Chandy->position.x)
			{
				Chandy->isHit = true;
				Chandy->coolDowntimer2 = 0.3;
				Chandy->velocity = (Vec2(-1000, 0));
				OpponentCandies[i]->getSprite()->removeFromParent();
				delete OpponentCandies[i];
				OpponentCandies.erase(OpponentCandies.begin() + i);
			}
			if (Opponent->position.x < Chandy->position.x)
			{
				Chandy->isHit = true;
				Chandy->coolDowntimer2 = 0.3;
				Chandy->velocity = (Vec2(1000, 0));
				OpponentCandies[i]->getSprite()->removeFromParent();
				delete OpponentCandies[i];
				OpponentCandies.erase(OpponentCandies.begin() + i);
			}
	

		}

	}

	for (int i = 0; i < OpponentCandies.size(); i++)
	{

		if (OpponentCandies[i]->position.y <= 0)
		{
			OpponentCandies[i]->getSprite()->removeFromParent();
			delete OpponentCandies[i];
			OpponentCandies.erase(OpponentCandies.begin() + i);
			i--;

		}

	}

	

//-----------------------------------------movement for first fighter-------------------------------------------------

	if (KeywPressed == true)
	{
		Chandy->JumpCounter--;
		if (Chandy->JumpCounter > 0)
		{
			Chandy->velocity.y = 1500;
		}
		
		

		
	}

	if (KeyboardSpacePressed == true)
	{
		if (Chandy->coolDowntimer <= 0.f) 
		{
			shoot(Chandy);
		}
		
		
	}


	if (KeydPressed == true)
	{
		if (Chandy->velocity.x < 0&&Chandy->isHit == false)
		{
			Chandy->velocity.x = 0;
		}
		Chandy->addForce(Vec2(500, 0));
		Chandy->getSprite()->setFlippedX(false);
		
	}
	if (KeyaPressed == true)
	{
		if (Chandy->velocity.x > 0&&Chandy->isHit == false)
		{
			Chandy->velocity.x = 0;
		}
		Chandy->addForce(Vec2(-500, 0));
		Chandy->getSprite()->setFlippedX(true);
		
	}
	
	if (KeysPressed == true)
	{
		if (Chandy->IsCollidingWith(DisplayedStage) == false)
		{
			Chandy->acceleration.y -= 10000;
			Chandy->velocity.y -= 10000;
		}


	}

	if (KeyaPressed == false && KeydPressed == false && Chandy->position.y <= 3000 && Chandy->isHit == false)//stops movement for chandy if you let go of the a or d
	{

		Chandy->velocity.x = 0;
		Chandy->acceleration.x = 0;
	}



	

	//---------------------------------movement for the other fighter-------------------------------------------

	
	

	if (KeyUpPressed == true )
	{
		Opponent->JumpCounter--;
		if (Opponent->JumpCounter > 0)
		{
			Opponent->velocity.y = 1500;
			
		}


	}


	if (KeyRightPressed == true)
	{
		if (Opponent->velocity.x < 0&&Opponent->isHit==false)
		{
			Opponent->velocity.x = 0;
		}
		Opponent->addForce(Vec2(500, 0));
		Opponent->getSprite()->setFlippedX(true);

	}
	if (KeyLeftPressed == true)
	{
		if (Opponent->velocity.x > 0&& Opponent->isHit == false)
		{
			Opponent->velocity.x = 0;
		}
		Opponent->addForce(Vec2(-500, 0));
		Opponent->getSprite()->setFlippedX(false);

	}

	if (KeyDownPressed == true)
	{
		if (Opponent->IsCollidingWith(DisplayedStage) == false)
		{
			Opponent->acceleration.y -= 10000;
			Opponent->velocity.y -= 10000;
		}
		

	}


	if (KeyLeftPressed == false && KeyRightPressed == false && Opponent->getSprite()->getBoundingBox().getMinY() <= DisplayedStage->getSprite()->getBoundingBox().getMaxY()&& Opponent->isHit == false)//stops movement for chandy if you let go of the a or d
	{
		Opponent->velocity.x = 0;
		Opponent->acceleration.x = 0;
	}


	if (KeyEnterPressed == true)
	{
		if (Opponent->coolDowntimer2 <= 0)
		{
			
			shoot(Opponent);
			

		}
	}



	//-----------------------------gives the charcters gravity ----------------------------------------------


	
		
		Chandy->addForce(gravity);


	
		Opponent->addForce(gravity);
	

	//-----------------------------udate the state of everything on the scene------------------------------------
	for (unsigned int i = 0; i < ChandyCandies.size(); i++)
	{
		//ChandyCandies[i]->addForce(gravity);
		ChandyCandies[i]->update(deltatime);

	}


	for (unsigned int i = 0; i < OpponentCandies.size(); i++)
	{
		//ChandyCandies[i]->addForce(gravity);
		OpponentCandies[i]->update(deltatime);


	}
//----------------------Hitstun-ish------------------------------------------


	Chandy->update(deltatime);

	
	Opponent->update(deltatime);

	//-------Update Character position when they fall off stage



	//------updates lives


	

	if (Chandy->position.y <= 0)
	{
		if (Chandy->position.y <=0&& Chandy->position.y > -100)
		{
			auto audio3 = SimpleAudioEngine::getInstance();
			// Set the lost life sound effect
			audio3->playEffect("Music/LostLife.mp3", false);
		}
	

		if (Chandy->position.x <DisplayedStage->getSprite()->getBoundingBox().getMidX())
		{
			ExplosionSprite->position=Vec2(0,0) ;
			ExplosionSprite->getSprite()->setPosition(0, 0);
			ExplosionSprite->getSprite()->setFlippedX(false);
		}

		if (Chandy->position.x >DisplayedStage->getSprite()->getBoundingBox().getMidX())
		{
			ExplosionSprite->position = Vec2(5000, 0);
			ExplosionSprite->getSprite()->setPosition(5000, 0);
			ExplosionSprite->getSprite()->setFlippedX(true);

		}
		Explosion();	
		loseLifeP1();
	}

		
	if (Opponent->position.y <= 0)
	{
		if (Opponent->position.y  <0&& Opponent->position.y>-100)
		{
			auto audio3 = SimpleAudioEngine::getInstance();
			// Set the lost life sound effect for opponent
			audio3->playEffect("Music/LostLife.mp3", false);
		}
	

		if (Opponent->position.x < DisplayedStage->getSprite()->getBoundingBox().getMidX())
		{
			ExplosionSprite->position = Vec2(0, 0);
			ExplosionSprite->getSprite()->setPosition(0, 0);
			ExplosionSprite->getSprite()->setFlippedX(false);
		}

		if (Opponent->position.x > DisplayedStage->getSprite()->getBoundingBox().getMidX())
		{
			ExplosionSprite->position = Vec2(5000, 0);
			ExplosionSprite->getSprite()->setPosition(5000, 0);
			ExplosionSprite->getSprite()->setFlippedX(true);

		}
		Explosion();
		loseLifeP2();
	}
	if (P2Lives == 0)
	{
		P1Win = new Character({ 2500,2000 }, "BackGrounds/WinP1.png");
		P1Win->getSprite()->setScale(2);
		
		
		
		this->addChild(P1Win->getSprite(), 3);
		

	}
	if (P1Lives == 0)
	{
		P2Win = new Character({ 2500,2000 }, "BackGrounds/WinP2.png");
		P2Win->getSprite()->setScale(2);
		this->addChild(P2Win->getSprite(), 3);

		
	}

}



void Hillside::loseLifeP1()
{


	P1Lives--;

	if (P1Lives == 2)
	{
		Chandy->position.y = 3000;
		Chandy->getSprite()->setPositionY(2000);
		Chandy->position.x = 1500;
		Chandy->getSprite()->setPositionX(1500);
		Three->getSprite()->removeFromParent();
		Two = new Character({ 520,2770 }, "Fighters/2.png");
		this->addChild(Two->getSprite(), 3);
	}

	
	if (P1Lives == 1)
	{
		Chandy->position.y = 3000;
		Chandy->getSprite()->setPositionY(2000);
		Chandy->position.x = 1500;
		Chandy->getSprite()->setPositionX(1500);
		Two->getSprite()->removeFromParent();
		One = new Character({ 520,2770 }, "Fighters/1.png");
		this->addChild(One->getSprite(), 3);
	}

	if (P1Lives == 0)
	{
		
		One->getSprite()->removeFromParent();
		Zero = new Character({ 520,2770 }, "Fighters/0.png");
		this->addChild(Zero->getSprite(), 3);
	}

	
}

void Hillside::loseLifeP2()
{
	P2Lives--;

	if (P2Lives == 2)
	{
		Opponent->position.y = 2000;
		Opponent->getSprite()->setPositionY(2000);
		Opponent->position.x = 2500;
		Opponent->getSprite()->setPositionX(2500);
		Three_->getSprite()->removeFromParent();
		Two_ = new Character({ 4820,2770 }, "Fighters/2.png");
		this->addChild(Two_->getSprite(), 3);
	}


	if (P2Lives == 1)
	{
		Opponent->position.y = 2000;
		Opponent->getSprite()->setPositionY(2000);
		Opponent->position.x = 2500;
		Opponent->getSprite()->setPositionX(2500);
		Two_->getSprite()->removeFromParent();
		One_ = new Character({ 4820,2770 }, "Fighters/1.png");
		this->addChild(One_->getSprite(), 3);
	}

	if (P2Lives == 0)
	{
		One_->getSprite()->removeFromParent();
		Zero_ = new Character({ 4820,2770 }, "Fighters/0.png");
		this->addChild(Zero_->getSprite(), 3);
	}
}


void Hillside::shoot(Fighter *theFighter)
{
	if (theFighter->P1 == false)
	{
		if (Opponent->getSprite()->isFlippedX() == true)
		{
			// timer ran out; react here
			OpponentCandy = new Character({ Opponent->position.x,Opponent->position.y }, "Fighters/PlaceHolder.png");
			OpponentCandy->IsBullet = true;
			OpponentCandy->fromOtherCharacter = true;
			OpponentCandy->velocity = (Vec2(5000, 0));
			OpponentCandies.push_back(OpponentCandy);
			this->addChild(OpponentCandy->getSprite(), 2);
			Opponent->coolDowntimer2 = 0.5;

			// Gun hit noise
			auto audio = SimpleAudioEngine::getInstance();
			// Play sound effect just once
			audio->playEffect("Music/GunShoot.wav", false, 1.0f, 1.0f, 1.0f);
		}
		if (Opponent->getSprite()->isFlippedX() == false)
		{
			// timer ran out; react here
			OpponentCandy = new Character({ Opponent->position.x,Opponent->position.y }, "Fighters/PlaceHolder.png");
			OpponentCandy->IsBullet = true;
			OpponentCandy->fromOtherCharacter = true;
			OpponentCandy->velocity = (Vec2(-5000, 0));
			OpponentCandies.push_back(OpponentCandy);
			this->addChild(OpponentCandy->getSprite(), 2);
			Opponent->coolDowntimer2 = 0.5;

			// Gun hit noise
			auto audio = SimpleAudioEngine::getInstance();
			// Play sound effect just once
			audio->playEffect("Music/GunShoot.wav", false, 1.0f, 1.0f, 1.0f);
		}
	}

	if (theFighter->P1 == true)
	{
		if (Chandy->getSprite()->isFlippedX() == true)
		{
			// timer ran out; react here
			ChandyCandy = new Character({ Chandy->position.x,Chandy->position.y }, "Fighters/PlaceHolder.png");
			ChandyCandy->IsBullet = true;
			ChandyCandy->fromOtherCharacter = false;
			ChandyCandy->velocity = (Vec2(-5000, 0));
			ChandyCandies.push_back(ChandyCandy);
			this->addChild(ChandyCandy->getSprite(), 2);
			Chandy->coolDowntimer = 0.5;

			// Gun hit noise
			auto audio = SimpleAudioEngine::getInstance();
			// Play sound effect just once
			audio->playEffect("Music/GunShoot.wav", false, 1.0f, 1.0f, 1.0f);
		}
		if (Chandy->getSprite()->isFlippedX() == false)
		{
			// timer ran out; react here
			ChandyCandy = new Character({ Chandy->position.x,Chandy->position.y }, "Fighters/PlaceHolder.png");
			ChandyCandy->IsBullet = true;
			ChandyCandy->fromOtherCharacter = false;
			ChandyCandy->velocity = (Vec2(5000, 0));
			ChandyCandies.push_back(ChandyCandy);
			this->addChild(ChandyCandy->getSprite(), 2);
			Chandy->coolDowntimer = 0.5;

			// Gun hit noise
			auto audio = SimpleAudioEngine::getInstance();
			// Play sound effect just once
			audio->playEffect("Music/GunShoot.wav", false, 1.0f, 1.0f, 1.0f);
		}
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
	if (Num == 1)
	{
		//Initialize the Background 
		auto Sprite = Sprite::create("BackGrounds/Hillside Stage.png");
		if (Sprite == nullptr)
		{
			problemLoading("'BackGrounds/Hillside Stage.png'");
		}
		else
		{
			Sprite->setPosition(Vec2(2500, 1500));
			Sprite->setScale(0.2575);
			this->addChild(Sprite, 2);
		}

	}

	if (Num== 2)
	{
		//Initialize the Background 
		auto Sprite = Sprite::create("BackGrounds/HillSide.png");
		if (Sprite == nullptr)
		{
			problemLoading("'BackGrounds/HillSide.png'");
		}
		else
		{
			Sprite->setPosition(Vec2(2500, 1500));
			Sprite->setScale(0.2575);
			this->addChild(Sprite, 2);
		}

	}

	if (Num == 3)
	{
		//Initialize the Background 
		auto Sprite = Sprite::create("BackGrounds/Sewer.png");
		if (Sprite == nullptr)
		{
			problemLoading("'BackGrounds/Sewer.png'");
		}
		else
		{
			Sprite->setPosition(Vec2(2500, 1500));
			Sprite->setScale(0.2575);
			this->addChild(Sprite, 2);
		}

	}


	//Initialize the Stage


	//this is the platform
	DisplayedStage= new Character({ 2500,505 }, "Platforms/Platform 2.png");
	this->addChild(DisplayedStage->getSprite(), 2);


	//Displaying lives     
	ChandyLogo = new Character({ 200,2700 }, "Fighters/Lifesymbol.png");
	this->addChild(ChandyLogo->getSprite(), 3);

	x = new Character({ 350,2760 }, "Fighters/x.png");
	this->addChild(x->getSprite(), 3);

	Three = new Character({ 520,2770 }, "Fighters/3.png");
	this->addChild(Three->getSprite(), 3);


	OpponentLogo = new Character({ 4470,2700 }, "Fighters/Lifesymbol2.png");
	this->addChild(OpponentLogo->getSprite(), 3);

	x_ = new Character({ 4650,2760 }, "Fighters/x.png");
	this->addChild(x_->getSprite(), 3);

	Three_ = new Character({ 4820,2770 }, "Fighters/3.png");
	this->addChild(Three_->getSprite(), 3);



	//Display the hook
	

	//Initialize the fighters
	Chandy = new Fighter({ 1500,2500 }, "Fighters/Chandy Sprite.png");
	Chandy->coolDowntimer = 0.25;
	Chandy->IsBullet=false;
	Chandy->isHit = false;
	Chandy->P1 = true;
	initializeIdleAnimP1();
	initializeJumpingAnimP1();
	initializeFallingAnimP1();
	initializeRunningAnimP1();
	Chandy->initRunAnim(P1RunningFrames, P1RunningFrames.size());
	Chandy->initIdleAnim(P1IdleFrames, P1IdleFrames.size());
	Chandy->initJumpAnim(P1JumpingFrames, P1JumpingFrames.size());
	Chandy->initFallAnim(P1FallingFrames, P1FallingFrames.size());
	this->addChild(Chandy->getSprite(), 3);

	Opponent = new Fighter({ 2500, 2500 }, "Fighters/Alt Chandy Sprite.png");
	Opponent->coolDowntimer2 = 0.25;
	Opponent->IsBullet = false;
	Opponent->isHit = false;
	Opponent->P1 = false;
	initializeIdleAnimP2();
	initializeJumpingAnimP2();
	initializeFallingAnimP2();
	initializeRunningAnimP2();
	Opponent->initRunAnim(P2RunningFrames, P2RunningFrames.size());
	Opponent->initIdleAnim(P2IdleFrames, P2IdleFrames.size());
	Opponent->initJumpAnim(P2JumpingFrames, P2JumpingFrames.size());
	Opponent->initFallAnim(P2FallingFrames, P2FallingFrames.size());
	this->addChild(Opponent->getSprite(), 3);

	ExplosionSprite = new Character({ 100, 100 }, "Effects/Explosion.png");
	ExplosionSprite->coolDowntimer2 = 0.25;
	ExplosionSprite->IsBullet = false;
	ExplosionSprite->isHit = false;
	
	this->addChild(ExplosionSprite->getSprite(), 3);

}

void Hillside::initHitBoxes()
{
	
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
		if (keyCode == EventKeyboard::KeyCode::KEY_Q)
		{
			KeyqPressed = true;

		}

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

		if (keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER)
		{
			std::cout << "Space Bar Was Released!" << std::endl;
			KeyEnterPressed = true;

		}


	};


	//On Key Released
	keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_Q)
		{
			KeyqPressed = false;

		}
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

		// If Statement for Enter Pressed
		if (keyCode == EventKeyboard::KeyCode::KEY_KP_ENTER)
		{
			std::cout << "Space Bar Was Released!" << std::endl;
			KeyEnterPressed = false;

		}
	};


	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void Hillside::onExit()
{
	/*_eventDispatcher->removeAllEventListeners();*/
	Scene::onExit();
	std::cout << "Exited!" << std::endl;
}

void Hillside::initializeIdleAnimP1()
{
	
	P1RunningFrames.push_back("Fighters/Chandy Idle 1.png");
}

void Hillside::initializeRunningAnimP1()
{
	P1IdleFrames.push_back("Fighters/Chandy Running 1.png");
	P1IdleFrames.push_back("Fighters/Chandy Running 1.png");
	P1IdleFrames.push_back("Fighters/Chandy Running 2.png");
	P1IdleFrames.push_back("Fighters/Chandy Running 2.png");
	P1IdleFrames.push_back("Fighters/Chandy Running 3.png");
	P1IdleFrames.push_back("Fighters/Chandy Running 3.png");
	
	
}

void Hillside::initializeJumpingAnimP1()
{
	P1JumpingFrames.push_back("Fighters/Chandy Jump.png");
	P1JumpingFrames.push_back("Fighters/Chandy Jump 2.png");
}

void Hillside::initializeFallingAnimP1()
{
	P1FallingFrames.push_back("Fighters/Chandy Fall.png");
}

void Hillside::initializeIdleAnimP2()
{
	P2IdleFrames.push_back("Fighters/Alt Chandy Idle 1.png");
}

void Hillside::initializeRunningAnimP2()
{
	P2RunningFrames.push_back("Fighters/Alt Chandy Running 1.png");
	P2RunningFrames.push_back("Fighters/Alt Chandy Running 2.png");
	P2RunningFrames.push_back("Fighters/Alt Chandy Running 3.png");
}

void Hillside::initializeJumpingAnimP2()
{
	P2JumpingFrames.push_back("Fighters/Alt Chandy Jump.png");
}

void Hillside::initializeFallingAnimP2()
{
	P2JumpingFrames.push_back("Fighters/Alt Chandy Fall.png");
}

void Hillside::Explosion()
{
	initializeExplosion();
	createExplosion(ExplosionFrames,ExplosionFrames.size());
	PlayExplosion();

}

void Hillside::initializeExplosion()
{
	ExplosionFrames.push_back("Effects/Explosion.png");
	ExplosionFrames.push_back("Effects/Explosion 2.png");
	ExplosionFrames.push_back("Effects/Explosion 3.png");
	ExplosionFrames.push_back("Effects/Explosion 4.png");
	ExplosionFrames.push_back("Effects/Explosion 5.png");
	ExplosionFrames.push_back("Effects/Explosion 6.png");
	ExplosionFrames.push_back("Effects/Explosion.png");
}

void Hillside::createExplosion(std::vector<std::string> Frames, int NumOfFrames)
{
	explosion = Animation::create();

	for (unsigned int i = 0; i < NumOfFrames; i++)
	{
		explosion->retain();
		explosion->addSpriteFrameWithFileName(Frames[i]);
	}


	explosion->setDelayPerUnit(0.1);
	explosion->setLoops(1);

}

void Hillside::PlayExplosion()
{
	ExplosionSprite->getSprite()->runAction(Animate::create(explosion));
	
}
