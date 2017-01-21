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
	// 물리적 위치를 이용해서 스프라이트의 위치를 갱신한다.

	// velocityIterations : 바디들을 정상적으로 이동시키기 위해서 필요한 충돌들을 반복적으로 계산
	// positionIterations : 조인트 분리와, 겹침현상을 줄이기 위해서 바디의 위치를 반복적으로 적용
	// 값이 클수록 정확한 연산이 가능하지만 성능이 떨어진다.

	// 프로젝트 생성시 기본값
	//    int velocityIterations = 8;
	//    int positionIterations = 1;

	// 매뉴얼상의 권장값
	int velocityIterations = 8;
	int positionIterations = 3;

	// Step : 물리 세계를 시뮬레이션한다.
	_world->Step(dt, velocityIterations, positionIterations);

	// 모든 물리 객체들은 링크드 리스트에 저장되어 참조해 볼 수 있도록 구현되어 있다.
	// 만들어진 객체 만큼 루프를 돌리면서 바디에 붙인 스프라이트를 여기서 제어한다.
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




