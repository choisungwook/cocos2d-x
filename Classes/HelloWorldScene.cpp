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
    //pull test 주석	
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
        return false;
    }   
		
	//캐릭터 초기화 및 생성 
	initalizeCharacter();

	// 적 초기화 및 생성 ( 1초 )
	this->schedule(schedule_selector(HelloWorld::initializeEnemy), 1.0f);
	// 1초후 게임 시작
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
	//적 이동 
	//벽면 충돌검사
	for (auto& enemy : vector_enemies) {
		enemy->move();		
	}

	//캐릭터 충돌검사
	for (auto iter_enemy = vector_enemies.begin(); iter_enemy != vector_enemies.end();)
	{		
		if (sprite_Character->collisionWithEnemy(*iter_enemy)) {
			removeChild(*iter_enemy); //auto relase속성 때문에 수동으로 release를 하면 안될 것같다.
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
	//캐릭터 sprite 생성
	sprite_Character = MyCharacter::create("character/1.png");
	sprite_Character->setPosition(ccp((VisibleRect::getVisibleRect().size.width / 2), (VisibleRect::getVisibleRect().size.height / 2)));
	this->addChild(sprite_Character);
	
	//충돌박스 그리기
	auto draw = DrawNode::create();
	auto checkBox = sprite_Character->collisionRegion();
	draw->drawRect(checkBox.origin, checkBox.origin + checkBox.size, Color4F(1, 0, 0, 1));
	draw->setPosition(ccp(-VisibleRect::getVisibleRect().size.width/2 + sprite_Character->getContentSize().width/2,
		-VisibleRect::getVisibleRect().size.height/2 + sprite_Character->getContentSize().height/2));
	sprite_Character->addChild(draw);
	
	//애니메이션
	//plist를 이용하는 편이 리소스를 줄이지만 유료프로그램밖에 없으므로
	//일일이 이미지를 애니메이션에 추가한다. ㅜ.ㅜ
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
