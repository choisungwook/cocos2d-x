#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"
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

	//메뉴 생성
	initalizeMenu();
	//캐릭터 초기화 및 생성 
	initalizeCharacter();
	// 적 초기화 및 생성 ( 1초 )
	this->schedule(schedule_selector(HelloWorld::initializeEnemy), 1.0f);
	// 1초후 게임 시작
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
	auto sprButton = MenuItemImage::create("power.png", "power1.png", CC_CALLBACK_1(HelloWorld::ButtonCallback, this));
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
	UserDefault::getInstance()->setDoubleForKey("data", chkTime);
	UserDefault::getInstance()->flush();
}

void HelloWorld::LoadData() {
	chkTime	= UserDefault::getInstance()->getDoubleForKey("data");
}


/*******************************************
Game menu
********************************************/

void HelloWorld::OptionCallback(Ref* pSender)
{
	log("Option open");

	if (isPause == false) {
		isPause = true;
		Director::getInstance()->getScheduler()->pauseTarget(this); //스케줄러 정지

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

		auto CloseGameButton = MenuItemImage::create("endgame.jpg", "endgame.jpg", CC_CALLBACK_1(HelloWorld::CloseGameCallback, this));
		auto menu = Menu::create(returnButton, CloseGameButton, NULL);
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
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::ButtonCallback(Ref* pSender)
{
	log("callback");
	//item button call back
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
	//공 움직임 
	//벽면 충돌검사
	for (auto& enemy : vector_enemies) {
		enemy->move();
	}

	//캐릭터 충돌검사 추가 예정
}

/*******************************************
	Character
********************************************/

void HelloWorld::initalizeCharacter() {
	//캐릭터 sprite 생성
	sprite_Character = MyCharacter::create("character/1.png");
	sprite_Character->setPosition(ccp((VisibleRect::getVisibleRect().size.width / 2), (VisibleRect::getVisibleRect().size.width / 2)));
	this->addChild(sprite_Character);

	//애니메이션
	//plist를 이용하는 편이 리소스를 줄이지만 유료프로그램밖에 없으므로
	//일일이 이미지를 애니메이션에 추가한다. ㅜ.ㅜ
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);	
}

/*******************************************
	Enemy
********************************************/

void HelloWorld::initializeEnemy(float dt)
{
	//적 이미지 가져오기
	Enemy* enemy = Enemy::create("enemy.png");

	//적 생성하는 방향 결정
	int sides = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
	int gap = -3;

	if (sides == 1) { //상
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width *0.25, origin.y + VisibleRect::getVisibleRect().size.width + gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.5, origin.y + VisibleRect::getVisibleRect().size.width + gap));
		else if (pos == 3)    enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.75, origin.y + VisibleRect::getVisibleRect().size.width + gap));
	}
	else if (sides == 2) // 하
	{
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.25, origin.y - gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.5, origin.y - gap));
		else if (pos == 3)   enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.75, origin.y - gap));
	}
	else if (sides == 3) // 좌
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.8));
	}
	else if (sides == 4) // 우
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.8));
	}
	
	//적 화면에 뿌림
	this->addChild(enemy);

	//적 벡터에 등록, 적스프라이트, 프레임당 이동하는 x,y값
	enemy->setvelocity(Vec2(2, 2));
	vector_enemies.pushBack(enemy);
}

/*******************************************
	Touch Event
********************************************/
bool HelloWorld::onTouch(cocos2d::Touch* touch, cocos2d::Event* event) {
	
	return false;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
	
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {

}
