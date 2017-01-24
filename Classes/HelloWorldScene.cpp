#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"
#include "MenuScene.h"
#include <string>

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

	//create the background
	background = Sprite::create("background2.png");	
	background->setPosition(VisibleRect::getVisibleRect().size.width/2, VisibleRect::getVisibleRect().size.height/2);
	addChild(background);

	//dataLoading
	LoadData();

	//�޴� ����
	initalizeMenu();
	initalizeCharacter();

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

	this->schedule(schedule_selector(HelloWorld::initializeEnemy), 1.0f);
	// 1초후 게임 ?�작
	this->scheduleOnce(schedule_selector(HelloWorld::startGame), 1.0f);
	// time counting 0.1s
	initTimer();
	this->schedule(schedule_selector(HelloWorld::UpdateTimer), 0.1f);

    return true;
}

void HelloWorld::initalizeMenu()
{
	//test option button
	auto sprOption = MenuItemImage::create("settings.png", "settings.png", CC_CALLBACK_1(HelloWorld::OptionCallback, this));
	sprOption->setScale(0.5f);

	auto menuOption = Menu::create(sprOption, NULL);
	menuOption->setPosition(ccp((VisibleRect::getVisibleRect().size.width*0.9), (VisibleRect::getVisibleRect().size.height*0.9)));
	this->addChild(menuOption, 1);

	log("%f %f", (VisibleRect::getVisibleRect().size.width*0.9, VisibleRect::getVisibleRect().size.height*0.9));



	//item button
	MenuItemImage* sprButton;
	
	if (getItem3 == 1)
		sprButton = MenuItemImage::create("3.png", "3.png", CC_CALLBACK_1(HelloWorld::Button3Callback, this));
	else if (getItem2 == 1)
		sprButton = MenuItemImage::create("2.png", "2.png", CC_CALLBACK_1(HelloWorld::Button2Callback, this));
    else if(getItem1 == 1)
		sprButton = MenuItemImage::create("1.png", "1.png", CC_CALLBACK_1(HelloWorld::Button1Callback, this));
	else
	{
		sprButton = MenuItemImage::create("power.png", "power.png", CC_CALLBACK_1(HelloWorld::ButtonCallback, this));
		sprButton->setOpacity(100);
	}
	
	sprButton->setScale(0.7f);
	
	auto menu = Menu::create(sprButton, NULL);
	menu->setPosition(ccp(VisibleRect::getVisibleRect().size.width*0.9, VisibleRect::getVisibleRect().size.height*0.2));
	this->addChild(menu, 1);

	/*
	auto sprtest = Sprite::create("1.jpg");
	sprtest->setPosition(menuOption->getPosition());
	this->addChild(sprtest);
	*/
}

/*******************************************
	timer
********************************************/
void HelloWorld::initTimer()
{
	timerLabel = Label::createWithSystemFont("", "Ariel", 20);
	timerLabel->setColor(Color3B::ORANGE);
	timerLabel->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height*0.9);
	this->addChild(timerLabel);
}
void HelloWorld::UpdateTimer(float dt)
{
	chkTime += 0.1;
	char timeScore[100] = { 0 };
	sprintf(timeScore, "%.1f", chkTime);
	
	timerLabel->setString(timeScore);
}

/*******************************************
	Save data (testing)
********************************************/
void HelloWorld::SaveData() {
	
	LoadData();
	if (MaxTime < (int)chkTime)
	{
		UserDefault::getInstance()->setDoubleForKey("data", chkTime);
		UserDefault::getInstance()->flush();
	}
}

void HelloWorld::LoadData() {
	MaxTime = UserDefault::getInstance()->getDoubleForKey("data");
	getItem1 = UserDefault::getInstance()->getIntegerForKey("item1");
	getItem2 = UserDefault::getInstance()->getIntegerForKey("item2");
	getItem3 = UserDefault::getInstance()->getIntegerForKey("item3");
}


/*******************************************
	Game menu
********************************************/

void HelloWorld::OptionCallback(Ref* pSender)
{
	log("Option open");

	if (isPause == false) {
		isPause = true;
		Director::getInstance()->getScheduler()->pauseTarget(this); //�����ٷ� ����

		if (OptionLayer == NULL) {
			OptionLayer = Layer::create();
			this->addChild(OptionLayer, 2);
		}

		sprite_Character->stopAllActions();

		Rect rectOption = OptionLayer->getBoundingBox();

		rect = Sprite::create("option.jpg");
		rect->setOpacity(150);
		rect->setPosition(Point(rectOption.getMaxX() / 2, rectOption.getMaxY() / 2));
		OptionLayer->addChild(rect);

		auto returnButton = MenuItemImage::create("returngame.jpg", "returngame.jpg", CC_CALLBACK_1(HelloWorld::ReturnGameCallback, this));
		auto backButton = MenuItemImage::create("backgame.jpg", "backgame.jpg", CC_CALLBACK_1(HelloWorld::ReturnScene, this));
		auto CloseGameButton = MenuItemImage::create("endgame.jpg", "endgame.jpg", CC_CALLBACK_1(HelloWorld::CloseGameCallback, this));
		auto menu = Menu::create(returnButton, backButton, CloseGameButton, NULL);
		menu->setOpacity(180);
		menu->alignItemsVertically();
		menu->setPosition(ccp(rectOption.getMaxX() / 2, rectOption.getMaxY() / 2));
		OptionLayer->addChild(menu);
	}
	else {
		isPause = false;
		Director::getInstance()->getScheduler()->resumeTarget(this);
		OptionLayer->removeAllChildren();
		sprite_Character->resume();
	}
}

void HelloWorld::ReturnGameCallback(Ref* pSender)
{
	isPause = false;
	Director::getInstance()->getScheduler()->resumeTarget(this);
	OptionLayer->removeAllChildren();
	sprite_Character->resume();
}

void HelloWorld::CloseGameCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	SaveData();
	Director::getInstance()->end();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::Button1Callback(Ref* pSender)
{
	log("callback 1");
	//item button call back
}
void HelloWorld::Button2Callback(Ref* pSender)
{
	log("callback 2");
	//item button call back
}
void HelloWorld::Button3Callback(Ref* pSender)
{
	log("callback 3");
	//item button call back
}
void HelloWorld::ButtonCallback(Ref* pSender)
{
	log("callback not item");
	//item button call back
}

void HelloWorld::ReturnScene(Ref* pSender)
{
	SaveData(); // max Time save
	auto pTran = MenuScene::createScene();
	Director::getInstance()->replaceScene(pTran);
}


/*******************************************
	Game Update
********************************************/

void HelloWorld::startGame(float dt)
{
	isPlaying = true;

	this->schedule(schedule_selector(HelloWorld::gameLogic), 2.0f / 60.0f);
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
			MessageBox("Collision",""); // test message box
			removeChild(*iter_enemy); 
			iter_enemy = vector_enemies.erase(iter_enemy);			
		}
		else {
			++iter_enemy;
		}
	}
}

/*******************************************
	Character
********************************************/

//initialize the character
void HelloWorld::initalizeCharacter() {
	//create the character sprite
	sprite_Character = MyCharacter::create("me.png");
	sprite_Character->setPosition(ccp((VisibleRect::getVisibleRect().size.width / 2), (VisibleRect::getVisibleRect().size.height / 2)));
	this->addChild(sprite_Character);
}

/*******************************************
	Enemy
********************************************/

void HelloWorld::initializeEnemy(float dt)
{
	Enemy* enemy = Enemy::create("ball.png");

	int sides = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
	int gap = -3;

	if (sides == 1) { //top
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width *0.25, origin.y + VisibleRect::getVisibleRect().size.width + gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.5, origin.y + VisibleRect::getVisibleRect().size.width + gap));
		else if (pos == 3)    enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.75, origin.y + VisibleRect::getVisibleRect().size.width + gap));
	}
	else if (sides == 2) // bottom
	{
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.25, origin.y - gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.5, origin.y - gap));
		else if (pos == 3)   enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.75, origin.y - gap));
	}
	else if (sides == 3) // east
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.8));
	}
	else if (sides == 4) // west
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.8));
	}

	this->addChild(enemy);

	//initalize the speed
	enemy->setvelocity(Vec2(2, 2));
	vector_enemies.pushBack(enemy);
}

/*******************************************
	Touch Event
********************************************/

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	pos_TouchBefore = touch->getLocation();
	pos_SpriteBefore = sprite_Character->getPosition();

	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {

	auto pos_cur = touch->getLocation();
	float diff_x = pos_cur.x - pos_TouchBefore.x;
	float diff_y = pos_cur.y - pos_TouchBefore.y;

	float x = pos_SpriteBefore.x + diff_x;
	float y = pos_SpriteBefore.y + diff_y;

	//âũ�� �˻�
	if (x > max_x) x = max_x;
	if (x < min_x) x = min_x;
	if (y > max_y) y = max_y;
	if (y < min_y) y = min_y;

	sprite_Character->setPosition(ccp(x, y));

}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {
	
}
