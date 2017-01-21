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
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
    {
        return false;
    }

	_screenSize = Director::getInstance()->getWinSize();
	initPhysics();
	scheduleUpdate();
	schedule(schedule_selector(HelloWorld::initializeEnemy), 1.0f);
	//schedule(schedule_selector(HelloWorld::logic), 0.1f);

	//listen for touches
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	min_x = 0 + character->getContentSize().width / 2;
	max_x = _screenSize.width - character->getContentSize().width / 2;
	min_y = 0 + character->getContentSize().height / 2;
	max_y = _screenSize.height - character->getContentSize().height / 2;
	
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
		
	//_debugDraw = new (std::nothrow) GLESDebugDraw(PTM_RATIO);
	//_world->SetDebugDraw(_debugDraw);
	//uint32 flags = 0;
	//flags += b2Draw::e_shapeBit;
	//// flags += b2Draw::e_jointBit;
	//// flags += b2Draw::e_aabbBit;
	//// flags += b2Draw::e_pairBit;
	//// flags += b2Draw::e_centerOfMassBit;
	//_debugDraw->SetFlags(flags);

	character = Character::create(this, Vec2(_screenSize.width/2, _screenSize.height/2), 0);
	addChild(character);

	//create table sides
	b2BodyDef tableBodyDef;
	tableBodyDef.position.Set(0, 0);
	auto tableBody = _world->CreateBody(&tableBodyDef);

	addWall(_screenSize.width, 0, (_screenSize.width / 2), 0); //CEIL
	addWall(_screenSize.width, 0, (_screenSize.width / 2), _screenSize.height); //BOTTOM
	addWall(0, _screenSize.height, 0, (_screenSize.height / 2)); //LEFT
	addWall(0, _screenSize.height, _screenSize.width, (_screenSize.height / 2)); //RIGHT
}

void HelloWorld::update(float dt)
{
	//default value
	int velocityIterations = 8;
	int positionIterations = 1;

	for (auto ball : _balls) {
		ball->update(dt);
	}

	_world->Step(dt, velocityIterations, positionIterations);

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

void HelloWorld::initializeEnemy(float dt)
{
	int sides = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
	int gap = 15;
	Vec2 vPos;

	//ceil
	if (sides == 1) { 
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) vPos.setPoint(origin.x + _screenSize.width *0.25, _screenSize.height - gap);
		else if (pos == 2) vPos.setPoint(origin.x + _screenSize.width*0.5,  _screenSize.height - gap);
		else if (pos == 3) vPos.setPoint(origin.x + _screenSize.width*0.75,  _screenSize.height - gap);
	}
	//bottom
	else if (sides == 2) 
	{
		int pos = 1 + (int)(3 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) vPos.setPoint(_screenSize.width*0.25, gap);
		else if (pos == 2) vPos.setPoint(_screenSize.width*0.5, gap);
		else if (pos == 3) vPos.setPoint(_screenSize.width*0.75, gap);
	}
	//left
	else if (sides == 3) 
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) vPos.setPoint(gap, + _screenSize.height*0.2);
		else if (pos == 2) vPos.setPoint(gap, _screenSize.height*0.4);
		else if (pos == 3) vPos.setPoint(gap, _screenSize.height*0.6);
		else if (pos == 4) vPos.setPoint(gap, _screenSize.height*0.8);
	}
	//right
	else if (sides == 4)
	{
		int pos = 1 + (int)(4 * rand() / (RAND_MAX + 1.0));
		if (pos == 1) vPos.setPoint(_screenSize.width - gap, _screenSize.height*0.2);
		else if (pos == 2) vPos.setPoint(_screenSize.width - gap, _screenSize.height*0.4);
		else if (pos == 3) vPos.setPoint(_screenSize.width - gap, _screenSize.height*0.6);
		else if (pos == 4) vPos.setPoint(_screenSize.width - gap, _screenSize.height*0.8);
	}

	auto ball = Ball::create(this, vPos, 0);
	this->addChild(ball);
	//enemy->setvelocity(Vec2(2, 2));
	_balls.pushBack(ball);
}



void HelloWorld::addWall(float w, float h, float px, float py)
{
	b2PolygonShape floorShape;

	floorShape.SetAsBox(w / PTM_RATIO, h / PTM_RATIO);
	b2FixtureDef floorFixture;
	floorFixture.density = 10;
	floorFixture.friction = 10;
	floorFixture.restitution = 0.5;
	floorFixture.shape = &floorShape;
	b2BodyDef floorBodyDef;

	floorBodyDef.position.Set(px / PTM_RATIO, py / PTM_RATIO);
	b2Body *floorBody = _world->CreateBody(&floorBodyDef);

	floorBody->CreateFixture(&floorFixture);
}

bool HelloWorld::onTouchBegan(Touch * touch, Event * event)
{
	Point tap = touch->getLocation();

	previousPos = tap;
	previousSpritePos = character->getPosition();

	return true;
}

void HelloWorld::onTouchMoved(Touch * touch, Event * event)
{
	Point tap = touch->getLocation();
	float diffx = tap.x - previousPos.x;
	float diffy = tap.y - previousPos.y;

	float x = previousSpritePos.x + diffx;
	float y = previousSpritePos.y + diffy;

	//창크기 검사
	if (x > max_x) x = max_x;
	if (x < min_x) x = min_x;
	if (y > max_y) y = max_y;
	if (y < min_y) y = min_y;

	Point pos = Vec2(x,y);
	character->getBody()->SetTransform(b2Vec2(pos.x / PTM_RATIO, pos.y / PTM_RATIO),character->getBody()->GetAngle());
}

void HelloWorld::onTouchEnded(Touch * touch, Event * event)
{
}

void HelloWorld::logic(float dt)
{
	
}

//void HelloWorld::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
//{
//	Layer::draw(renderer, transform, flags);
//	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
//	auto director = Director::getInstance();
//	CCASSERT(nullptr != director, "Director is null when setting matrix stack");
//		director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//	_modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//	_customCommand.init(_globalZOrder);
//	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this);
//	renderer->addCommand(&_customCommand);
//	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//}
//
//void HelloWorld::onDraw()
//{
//	Mat4 oldMV;
//
//	auto director = Director::getInstance();	
//	oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW,	_modelViewMV);
//	_world->DrawDebugData();
//	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW,	oldMV);
//}