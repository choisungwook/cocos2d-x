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

	//�޴� ����
	initalizeMenu();
	//ĳ���� �ʱ�ȭ �� ���� 
	initalizeCharacter();
	// �� �ʱ�ȭ �� ���� ( 1�� )
	this->schedule(schedule_selector(HelloWorld::initializeEnemy), 1.0f);
	// 1���� ���� ����
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
	//�� ������ 
	//���� �浹�˻�
	for (auto& enemy : vector_enemies) {
		enemy->move();
	}

	//ĳ���� �浹�˻� �߰� ����
}

/*******************************************
	Character
********************************************/

void HelloWorld::initalizeCharacter() {
	//ĳ���� sprite ����
	sprite_Character = MyCharacter::create("character/1.png");
	sprite_Character->setPosition(ccp((VisibleRect::getVisibleRect().size.width / 2), (VisibleRect::getVisibleRect().size.width / 2)));
	this->addChild(sprite_Character);

	//�ִϸ��̼�
	//plist�� �̿��ϴ� ���� ���ҽ��� �������� �������α׷��ۿ� �����Ƿ�
	//������ �̹����� �ִϸ��̼ǿ� �߰��Ѵ�. ��.��
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);	
}

/*******************************************
	Enemy
********************************************/

void HelloWorld::initializeEnemy(float dt)
{
	//�� �̹��� ��������
	Enemy* enemy = Enemy::create("enemy.png");

	//�� �����ϴ� ���� ����
	int sides = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
	int gap = -3;

	if (sides == 1) { //��
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width *0.25, origin.y + VisibleRect::getVisibleRect().size.width + gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.5, origin.y + VisibleRect::getVisibleRect().size.width + gap));
		else if (pos == 3)    enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.75, origin.y + VisibleRect::getVisibleRect().size.width + gap));
	}
	else if (sides == 2) // ��
	{
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.25, origin.y - gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.5, origin.y - gap));
		else if (pos == 3)   enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width*0.75, origin.y - gap));
	}
	else if (sides == 3) // ��
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x - gap, origin.y + VisibleRect::getVisibleRect().size.width*0.8));
	}
	else if (sides == 4) // ��
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x + VisibleRect::getVisibleRect().size.width + gap, origin.y + VisibleRect::getVisibleRect().size.width*0.8));
	}
	
	//�� ȭ�鿡 �Ѹ�
	this->addChild(enemy);

	//�� ���Ϳ� ���, ����������Ʈ, �����Ӵ� �̵��ϴ� x,y��
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
