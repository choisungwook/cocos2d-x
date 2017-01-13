#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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
	// enemyMovement.y가 음수이면 적이 내려오고 있는 것.
	// enemyMovement.y가 양수이면 적이 올라가고 있는 것.

	for (int i = 0; i < vecEnemy.size(); i++) {
		auto enemy = vecEnemy.at(i).first;
		auto enemyMovement = vecEnemy.at(i).second;


		enemy->setPosition(Point(enemy->getPosition().x + enemyMovement.x,
			enemy->getPosition().y + enemyMovement.y));

		// 벽면 충돌 체크
		if (enemy->getPosition().x > 480 || enemy->getPosition().x < 0)
			enemyMovement.x = -enemyMovement.x;

		if (enemy->getPosition().y > 320 || enemy->getPosition().y < 0)
			enemyMovement.y = -enemyMovement.y;

		vecEnemy.at(i).first = enemy;
		vecEnemy.at(i).second = enemyMovement;
	}

}

/*******************************************
	Character
********************************************/

void HelloWorld::initalizeCharacter() {
	//[sprite] 애니메이션관련 마우스로 움직일 캐릭터
	sprite_AnimationCharacter = Sprite::create("res/monster.png");
	auto texture = sprite_AnimationCharacter->getTexture();
	//[animation]
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 0; i < 4; i++) {
		animation->addSpriteFrameWithTexture(texture, Rect(i * 64, 0, 64, 64));
	}
	auto animate = Animate::create(animation);
	auto action_foreverRepeat = RepeatForever::create(animate);

	//[sprite] 마우스로 움직일 캐릭터
	sprite_Character = Sprite::create("res/monster.png", Rect(0, 0, 64, 64));
	sprite_Character->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite_Character);

	//액션 등록
	sprite_Character->runAction(action_foreverRepeat);

	//이벤트
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouch, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite_Character);
	
	//캐릭터가 화면 범위 밖에 나가지 못하도록 ...
	float character_width = sprite_Character->getContentSize().width;
	float character_height = sprite_Character->getContentSize().height;

	//캐릭터가 이동할 수 있는 최소,최대크기(상대적 거리)
	min_x = 0 + character_width / 2;
	max_x = visibleSize.width - character_width / 2;
	min_y = 0 + character_height / 2;
	max_y = visibleSize.height - character_height / 2;
}

/*******************************************
	Enemy
********************************************/

void HelloWorld::initializeEnemy(float dt)
{
	//srand((unsigned)time(NULL));

	visibleSize = Point(480, 320);

	//적 이미지 가져오기
	Sprite* enemy = Sprite::create("res/enemy.png");

	//적 생성
	int sides = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
	log("%d", sides);

	int gap = -3;

	if (sides == 1) { //상
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + visibleSize.width*0.25, origin.y + visibleSize.height + gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + visibleSize.width*0.5, origin.y + visibleSize.height + gap));
		else if (pos == 3)    enemy->setPosition(Vec2(origin.x + visibleSize.width*0.75, origin.y + visibleSize.height + gap));
	}
	else if (sides == 2) // 하
	{
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + visibleSize.width*0.25, origin.y - gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + visibleSize.width*0.5, origin.y - gap));
		else if (pos == 3)   enemy->setPosition(Vec2(origin.x + visibleSize.width*0.75, origin.y - gap));
	}
	else if (sides == 3) // 좌
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x - gap, origin.y + visibleSize.height*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x - gap, origin.y + visibleSize.height*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x - gap, origin.y + visibleSize.height*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x - gap, origin.y + visibleSize.height*0.8));
	}
	else if (sides == 4) // 우
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + visibleSize.width + gap, origin.y + visibleSize.height*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x + visibleSize.width + gap, origin.y + visibleSize.height*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x + visibleSize.width + gap, origin.y + visibleSize.height*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x + visibleSize.width + gap, origin.y + visibleSize.height*0.8));
	}

	//임시 사이즈 조정
	enemy->setScale(0.08f);

	log("new!!, %f, %f", enemy->getPositionX(), enemy->getPositionY());

	int x = 2, y = 2;

	if (RandomHelper::random_int(1, 100) < 25)
		x = -x;
	else if (RandomHelper::random_int(1, 100) >= 25 && RandomHelper::random_int(1, 100) < 50)
		y = -y;

	//적 화면에 뿌림
	this->addChild(enemy);

	//적 벡터에 등록, 적스프라이트, 프레임당 이동하는 x,y값
	vecEnemy.push_back({ enemy, Point(x,y) });
}

/*******************************************
	Touch Event
********************************************/
bool HelloWorld::onTouch(cocos2d::Touch* touch, cocos2d::Event* event) {
	pos_TouchBefore = touch->getLocation();
	pos_SpriteBefore = sprite_Character->getPosition();
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
	auto pos_cur = touch->getLocation();
	auto pos_character = sprite_Character->getPosition();
	float diff_x = pos_cur.x - pos_TouchBefore.x;
	float diff_y = pos_cur.y - pos_TouchBefore.y;

	float x = pos_SpriteBefore.x + diff_x;
	float y = pos_SpriteBefore.y + diff_y;
	
	//창크기 검사
	if (x > max_x) x = max_x;
	if (x < min_x) x = min_x;
	if (y > max_y) y = max_y;
	if (y < min_y) y = min_y;

	sprite_Character->setPosition(ccp(x, y));
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {



}

void HelloWorld::moveCharacter() {

}