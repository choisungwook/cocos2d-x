#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "character.h"
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
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
    {
        return false;
    }

	_screenSize = Director::getInstance()->getWinSize();
	initPhysics();
	scheduleUpdate();
    return true;
}

void HelloWorld::initPhysics()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	_world = new b2World(gravity);

	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);
	/*_collisionListener = new CollisionListener();
	_world->SetContactListener(_collisionListener);*/
		
	_debugDraw = new (std::nothrow) GLESDebugDraw(PTM_RATIO);
	_world->SetDebugDraw(_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	// flags += b2Draw::e_jointBit;
	// flags += b2Draw::e_aabbBit;
	// flags += b2Draw::e_pairBit;
	// flags += b2Draw::e_centerOfMassBit;
	_debugDraw->SetFlags(flags);



	//add balls
	float startX = _screenSize.width * 0.07;
	float startY = _screenSize.height * 0.92f;

	
	_balls = Vector<Ball *>(15);

	int col = 5;
	int colCnt = 0;
	startX = (_screenSize.width - 8 * BALL_RADIUS) * 0.5f;
	startY = _screenSize.height * 0.82f;
	float newX;
	float newY;
	int color;
	for (int i = 0; i < 10; i++) {
		if (i == 10) {
			color = kColorBlack;
		}
		else if (i % 2 == 0) {
			color = kColorYellow;
		}
		else {
			color = kColorRed;
		}
		if (colCnt < col) {
			newX = startX + colCnt * 2 * BALL_RADIUS;
			colCnt++;
		}
		else {
			startX += BALL_RADIUS;
			startY -= 2 * BALL_RADIUS;
			newX = startX;
			col--;
			colCnt = 1;
		}	
		newY = startY;
		auto ball = Ball::create(this, Vec2(newX, newY), color);
		//_gameBatchNode->addChild(ball, kMiddleground);
		_balls.pushBack(ball);
		addChild(ball);
	}
	auto character = Character::create(this, Vec2(_screenSize.width/2, _screenSize.height/2), color);
	addChild(character);

	//create table sides
	b2BodyDef tableBodyDef;
	tableBodyDef.position.Set(0, 0);
	auto tableBody = _world->CreateBody(&tableBodyDef);

	addWall(_screenSize.width, 10, (_screenSize.width / 2), 0); //CEIL
	addWall(_screenSize.width, 10, (_screenSize.width / 2), _screenSize.height); //CEIL
	addWall(10, _screenSize.height, 0, (_screenSize.height / 2)); //LEFT
	addWall(10, _screenSize.height, _screenSize.width, (_screenSize.height / 2)); //RIGHT

}

void HelloWorld::update(float dt)
{
	_world->Step(dt, 10, 10);

	for (auto ball : _balls) {

		ball->update(dt);
	}
	// ������ ��ġ�� �̿��ؼ� ��������Ʈ�� ��ġ�� �����Ѵ�.

	// velocityIterations : �ٵ���� ���������� �̵���Ű�� ���ؼ� �ʿ��� �浹���� �ݺ������� ���
	// positionIterations : ����Ʈ �и���, ��ħ������ ���̱� ���ؼ� �ٵ��� ��ġ�� �ݺ������� ����
	// ���� Ŭ���� ��Ȯ�� ������ ���������� ������ ��������.

	// ������Ʈ ������ �⺻��
	//    int velocityIterations = 8;
	//    int positionIterations = 1;

	// �Ŵ������ ���尪
	int velocityIterations = 8;
	int positionIterations = 3;

	// Step : ���� ���踦 �ùķ��̼��Ѵ�.
	_world->Step(dt, velocityIterations, positionIterations);

	// ��� ���� ��ü���� ��ũ�� ����Ʈ�� ����Ǿ� ������ �� �� �ֵ��� �����Ǿ� �ִ�.
	// ������� ��ü ��ŭ ������ �����鼭 �ٵ� ���� ��������Ʈ�� ���⼭ �����Ѵ�.
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr) {
			Sprite* spriteData = (Sprite *)b->GetUserData();
			// if ball is going too fast, turn on damping
			if (spriteData->getTag() == 1) {
				static int maxSpeed = 10;

				b2Vec2 velocity = b->GetLinearVelocity();
				float32 speed = velocity.Length();

				if (speed > maxSpeed) {
					b->SetLinearDamping(0.5);
				}
				else if (speed < maxSpeed) {
					b->SetLinearDamping(0.0);
				}
				continue;
			}

			spriteData->setPosition(Point(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			//spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

void HelloWorld::addWall(float w, float h, float px, float py)
{
	b2PolygonShape floorShape;

	floorShape.SetAsBox(w / PTM_RATIO, h / PTM_RATIO);
	b2FixtureDef floorFixture;
	floorFixture.density = 0;
	floorFixture.friction = 10;
	floorFixture.restitution = 0.5;
	floorFixture.shape = &floorShape;
	b2BodyDef floorBodyDef;

	floorBodyDef.position.Set(px / PTM_RATIO, py / PTM_RATIO);
	b2Body *floorBody = _world->CreateBody(&floorBodyDef);

	floorBody->CreateFixture(&floorFixture);
}

void HelloWorld::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
{
	//
	// IMPORTANT:
	// This is only for debug purposes
	// It is recommended to disable it
	//
	Layer::draw(renderer, transform, flags);
	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	auto director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when setting matrix stack");
		director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	_modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this);
	renderer->addCommand(&_customCommand);
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void HelloWorld::onDraw()
{
	auto director = Director::getInstance();
	Mat4 oldMV;
	oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW,
		_modelViewMV);
	_world->DrawDebugData();
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW,
		oldMV);
}




