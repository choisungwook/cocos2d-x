#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"
#include "MenuScene.h"
#include <string>
#include "resources.h"
#include "Gameover.h"
#include <random>
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
        return false;
    }   

	//set up
	initalizeBackground();
	initalizeMenu();
	initalizeCharacter();
	initalizeTimer();
	initializItem();
	
	// initalize Touch events
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// initalize screen values
	float character_width = sprite_Character->getContentSize().width;
	float character_height = sprite_Character->getContentSize().height;

	min_x = 0 + character_width / 2;
	max_x = VisibleRect::getVisibleRect().size.width - character_width / 2;
	min_y = 0 + character_height / 2;
	max_y = VisibleRect::getVisibleRect().size.height - character_height / 2;

	//initalize schedules
	this->schedule(schedule_selector(HelloWorld::initializeEnemy), 1.0f);
	this->scheduleOnce(schedule_selector(HelloWorld::startGame), 1.0f);
	this->schedule(schedule_selector(HelloWorld::UpdateTimer), 0.1f);

    return true;
}

/*******************************************
	initalize
********************************************/

void HelloWorld::initalizeBackground()
{
	//create the background
	sbackground = Sprite::create(background);
	sbackground->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2);
	addChild(sbackground);

	auto earth = Sprite::create("earth.png");
	earth->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2);
	earth->setOpacity(70);
	addChild(earth);

	auto moon = Sprite::create("moon.png");
	moon->setPosition(VisibleRect::getVisibleRect().size.width / 4, VisibleRect::getVisibleRect().size.height * 0.7);
	moon->setOpacity(90);
	addChild(moon);
}

void HelloWorld::initalizeMenu()
{
	auto sprOption = MenuItemImage::create(setting, setting, CC_CALLBACK_1(HelloWorld::OptionCallback, this));
	sprOption->setOpacity(80);
	auto menuOption = Menu::create(sprOption, NULL);
	menuOption->setPosition(ccp((VisibleRect::getVisibleRect().size.width*0.9), (VisibleRect::getVisibleRect().size.height*0.9)));
	this->addChild(menuOption, menuOrder);	
}

void HelloWorld::initalizeTimer()
{
	timerLabel = Label::createWithSystemFont("", "Ariel", 30);
	timerLabel->setColor(Color3B::WHITE);
	timerLabel->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height*0.9);
	this->addChild(timerLabel);

	eattimerLabel = Label::createWithSystemFont("", "Ariel", 30);
	eattimerLabel->setColor(Color3B::ORANGE);
	eattimerLabel->setPosition(VisibleRect::getVisibleRect().size.width * 0.7, VisibleRect::getVisibleRect().size.height*0.9);
	this->addChild(eattimerLabel);

	EatTime = 3.0f;
}

void HelloWorld::initalizeCharacter() {
	//create the character sprite
	sprite_Character = MyCharacter::create(character);
	sprite_Character->setPosition(ccp((VisibleRect::getVisibleRect().size.width / 2), (VisibleRect::getVisibleRect().size.height / 2)));
	this->addChild(sprite_Character);
}

void HelloWorld::initializeEnemy(float dt)
{
	Enemy* enemy = Enemy::create(ball);

	int sides = getballRand(1,4);
	int enemyRadius = enemy->get_radius();
	double ball_width = 0.0f;
	double ball_height = 0.0f;
	
	switch (sides) {
	case 1: //east
		ball_width = enemyRadius;
		ball_height = getballRand(enemyRadius, origin.y + VisibleRect::getVisibleRect().size.height - enemyRadius);

		enemy->setPosition(Vec2(ball_width, ball_height));
		break;
	case 2: //west
		ball_width = VisibleRect::getVisibleRect().size.width - enemyRadius;
		ball_height = getballRand(enemyRadius, origin.y + VisibleRect::getVisibleRect().size.height - enemyRadius);

		enemy->setPosition(Vec2(ball_width, ball_height));
		break;
	case 3: //north
		ball_width = getballRand(enemyRadius, origin.x + VisibleRect::getVisibleRect().size.width - enemyRadius);
		ball_height = origin.y + VisibleRect::getVisibleRect().size.height;

		enemy->setPosition(Vec2(ball_width, ball_height));
		break;
	case 4://south
		ball_width = getballRand(enemyRadius, origin.x + VisibleRect::getVisibleRect().size.width - enemyRadius);
		ball_height = enemyRadius;

		enemy->setPosition(Vec2(ball_width, ball_height));
		break;
	default:
		break;
	}
	
	this->addChild(enemy);

	//initalize the speed
	auto velocity_x = cocos2d::random(1, 7);
	auto velocity_y = cocos2d::random(1, 7);

	enemy->setvelocity(Vec2(velocity_x, velocity_y));
	vector_enemies.pushBack(enemy);
}

void HelloWorld::initializItem()
{
	if (ItemLayer == NULL) {
		ItemLayer = Layer::create();
		this->addChild(ItemLayer, 2);

		eatItem = MenuItemImage::create(Itemeat, Itemeat, CC_CALLBACK_1(HelloWorld::EatItemCallback, this));
		auto menu = Menu::create(eatItem, NULL);
		menu->setPosition(VisibleRect::getVisibleRect().size.width * 0.9, VisibleRect::getVisibleRect().size.width * 0.1);
		menu->alignItemsHorizontally();

		ItemLayer->addChild(menu);
	}
	else {
		eatItem->setVisible(true);
	}
}

double HelloWorld::getballRand(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::uniform_real_distribution<> dis{ min, max };
	
	return dis(gen);
}

/*******************************************
	schedule
********************************************/

void HelloWorld::UpdateTimer(float dt)
{
	chkTime += 0.1;	
	timerLabel->setString(StringUtils::format("%.1f", chkTime));

	if (sprite_Character->getstate() == state_Eat) {
		EatTime -= 0.1;
		eattimerLabel->setString(StringUtils::format("%.1f", EatTime));
	}
}

void HelloWorld::EatTimer(float dt)
{
	sprite_Character->setstate(state_Standard);
	EatTime = 3.0f;
	eattimerLabel->setVisible(false);
}

/*******************************************
	Callback Functions
********************************************/

void HelloWorld::OptionCallback(Ref* pSender)
{
	if (isPause == false) {
		isPause = true;
		Director::getInstance()->getScheduler()->pauseTarget(this);

		if (OptionLayer == NULL) {
			OptionLayer = Layer::create();
			this->addChild(OptionLayer, 2);
		}

		sprite_Character->stopAllActions();

		auto returnButton = MenuItemImage::create(resumegame, resumegame, CC_CALLBACK_1(HelloWorld::ReturnGameCallback, this));
		auto backButton = MenuItemImage::create(home, home, CC_CALLBACK_1(HelloWorld::ReturnScene, this));
		auto CloseGameButton = MenuItemImage::create(endgame, endgame, CC_CALLBACK_1(HelloWorld::CloseGameCallback, this));
		auto menu = Menu::create(returnButton, backButton, CloseGameButton, NULL);
		menu->setOpacity(180);
		menu->alignItemsVertically();

		OptionLayer->addChild(menu);
	}
	else {		
		Director::getInstance()->getScheduler()->resumeTarget(this);
		OptionLayer->removeAllChildren();

		isPause = false;
	}
}

void HelloWorld::ReturnGameCallback(Ref* pSender)
{
	isPause = false;
	Director::getInstance()->getScheduler()->resumeTarget(this);
	OptionLayer->removeAllChildren();
}

void HelloWorld::CloseGameCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	Director::getInstance()->end();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::ReturnScene(Ref* pSender)
{
	auto pTran = MenuScene::createScene();
	Director::getInstance()->replaceScene(pTran);
}

void HelloWorld::EatItemCallback(Ref * pSender)
{
	if (eatItem == NULL) return;
	sprite_Character->setstate(state_Eat);
	eatItem->setVisible(false);	

	this->scheduleOnce(schedule_selector(HelloWorld::EatTimer), 3.0f);

}


/*******************************************
	Game Update
********************************************/

void HelloWorld::startGame(float dt)
{
	isPause = false;

	this->schedule(schedule_selector(HelloWorld::gameLogic), gamespeed);
}

void HelloWorld::gameLogic(float dt)
{
	// move enemies
	for (auto& enemy : vector_enemies) {
		enemy->move();		
	}

	// check collision character with enemies
	for (auto iter_enemy = vector_enemies.begin(); iter_enemy != vector_enemies.end();)
	{		
		if (sprite_Character->collisionWithEnemy(*iter_enemy)) {
			if (sprite_Character->getstate() == state_Eat) {
				removeChild(*iter_enemy);
				iter_enemy = vector_enemies.erase(iter_enemy);
			}
			else {
				auto gameover = GameOverScene::createScene(chkTime);
				Director::getInstance()->replaceScene(gameover);

				removeChild(*iter_enemy);
				iter_enemy = vector_enemies.erase(iter_enemy);
			}
		}
		else {
			++iter_enemy;
		}
	}
}

/*******************************************
	Touch Event
********************************************/

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (isPause == true) return false;
	pos_TouchBefore = touch->getLocation();
	pos_SpriteBefore = sprite_Character->getPosition();

	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
	if (isPause == true) return;

	auto pos_cur = touch->getLocation();
	float diff_x = pos_cur.x - pos_TouchBefore.x;
	float diff_y = pos_cur.y - pos_TouchBefore.y;

	float x = pos_SpriteBefore.x + diff_x;
	float y = pos_SpriteBefore.y + diff_y;

	//Ã¢Å©±â °Ë»ç
	if (x > max_x) x = max_x;
	if (x < min_x) x = min_x;
	if (y > max_y) y = max_y;
	if (y < min_y) y = min_y;

	sprite_Character->setPosition(ccp(x, y));

}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {
	if (isPause == true) return;
}
