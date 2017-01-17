#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"

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
		
	//ĳ���� �ʱ�ȭ �� ���� 
	initalizeCharacter();
	// �� �ʱ�ȭ �� ���� ( 1�� )
	this->schedule(schedule_selector(HelloWorld::initializeEnemy), 1.0f);
	// 1���� ���� ����
	this->scheduleOnce(schedule_selector(HelloWorld::startGame), 1.0f);
	return true;
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
	//�� �̵� 
	//���� �浹�˻�
	for (auto& enemy : vector_enemies) {
		enemy->move();		
	}

	//ĳ���� �浹�˻�
	for (auto iter_enemy = vector_enemies.begin(); iter_enemy != vector_enemies.end();)
	{		
		if (sprite_Character->collisionWithEnemy(*iter_enemy)) {
			removeChild(*iter_enemy); //auto relase�Ӽ� ������ �������� release�� �ϸ� �ȵ� �Ͱ���.
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

	for (int i = 1; i <= 5; i++) {
		char imgpath[100] = { 0, };
		sprintf(imgpath, "character/%d.png", i);
		animation->addSpriteFrameWithFile(imgpath);
	}

	auto animate = Animate::create(animation);
	sprite_Character->runAction(RepeatForever::create(animate));
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
