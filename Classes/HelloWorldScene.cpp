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
	// ballMovement.y�� �����̸� ���� �������� �ִ� ��
	// ballMovement.y�� ����̸� ���� �ö󰡰� �ִ� ��
	std::vector<std::pair<cocos2d::Sprite*, cocos2d::Point>>::iterator enmyIterator;
	for (enmyIterator = vecEnemy.begin(); enmyIterator != vecEnemy.end(); ) {
		auto enemy = enmyIterator->first;
		auto enemyMovement = enmyIterator->second;

		enemy->setPosition(Point(enemy->getPosition().x + enemyMovement.x,
			enemy->getPosition().y + enemyMovement.y));

		// ���� �浹 üũ
		if (enemy->getPosition().x > visibleSize.width || enemy->getPosition().x < 0)
			enemyMovement.x = -enemyMovement.x;

		if (enemy->getPosition().y > visibleSize.height || enemy->getPosition().y < 0)
			enemyMovement.y = -enemyMovement.y;

		//ĳ���� �浹 üũ
		Rect charRect = sprite_Character->getBoundingBox();
		Rect enemyRect = enemy->getBoundingBox();

		if (charRect.intersectsRect(enemyRect)) {
			//MessageBox("Collision", "");
			this->removeChild(enemy);
			enemy->autorelease();
			enmyIterator = vecEnemy.erase(enmyIterator);
		}
		else {
			enmyIterator->first = enemy;
			enmyIterator->second = enemyMovement;
			enmyIterator++;
		}
	}
}

/*******************************************
	Character
********************************************/

void HelloWorld::initalizeCharacter() {
	//ĳ���� sprite ����
	sprite_Character = MyCharacter::create("character/1.png");
	sprite_Character->setPosition(ccp((visibleSize.width / 2), (visibleSize.height / 2)));
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
	//srand((unsigned)time(NULL));

	visibleSize = Point(480, 320);

	//�� �̹��� ��������
	Sprite* enemy = Sprite::create("res/enemy.png");

	//�� ����
	int sides = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
	log("%d", sides);

	int gap = -3;

	if (sides == 1) { //��
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + visibleSize.width*0.25, origin.y + visibleSize.height + gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + visibleSize.width*0.5, origin.y + visibleSize.height + gap));
		else if (pos == 3)    enemy->setPosition(Vec2(origin.x + visibleSize.width*0.75, origin.y + visibleSize.height + gap));
	}
	else if (sides == 2) // ��
	{
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + visibleSize.width*0.25, origin.y - gap));
		else if (pos == 2)   enemy->setPosition(Vec2(origin.x + visibleSize.width*0.5, origin.y - gap));
		else if (pos == 3)   enemy->setPosition(Vec2(origin.x + visibleSize.width*0.75, origin.y - gap));
	}
	else if (sides == 3) // ��
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x - gap, origin.y + visibleSize.height*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x - gap, origin.y + visibleSize.height*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x - gap, origin.y + visibleSize.height*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x - gap, origin.y + visibleSize.height*0.8));
	}
	else if (sides == 4) // ��
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) enemy->setPosition(Vec2(origin.x + visibleSize.width + gap, origin.y + visibleSize.height*0.2));
		else if (pos == 2) enemy->setPosition(Vec2(origin.x + visibleSize.width + gap, origin.y + visibleSize.height*0.4));
		else if (pos == 3) enemy->setPosition(Vec2(origin.x + visibleSize.width + gap, origin.y + visibleSize.height*0.6));
		else if (pos == 4) enemy->setPosition(Vec2(origin.x + visibleSize.width + gap, origin.y + visibleSize.height*0.8));
	}

	//�ӽ� ������ ����
	enemy->setScale(0.08f);

	log("new!!, %f, %f", enemy->getPositionX(), enemy->getPositionY());

	int x = 2, y = 2;

	if (RandomHelper::random_int(1, 100) < 25)
		x = -x;
	else if (RandomHelper::random_int(1, 100) >= 25 && RandomHelper::random_int(1, 100) < 50)
		y = -y;

	//�� ȭ�鿡 �Ѹ�
	this->addChild(enemy);

	//�� ���Ϳ� ���, ����������Ʈ, �����Ӵ� �̵��ϴ� x,y��
	vecEnemy.push_back({ enemy, Point(x,y) });
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
