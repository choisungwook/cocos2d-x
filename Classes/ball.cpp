#include "Ball.h"
#include "HelloWorldScene.h"

Ball::~Ball() {}

Ball::Ball(HelloWorld * game, Point position, int color) : b2Sprite(game) {
	_startPosition = position;
	_color = color;
	_inPlay = true;
}

Ball* Ball::create(HelloWorld * game, Point position, int color) {
	auto sprite = new Ball(game, position, color);
	if (sprite) {
		sprite->initBall();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Ball::initBall() {
	//create box2d body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	
	_body = _game->getWorld()->CreateBody(&bodyDef);
	_body->SetSleepingAllowed(true);
	_body->SetLinearDamping(1.2);
	_body->SetAngularDamping(0.8);
	_body->SetLinearVelocity(b2Vec2(50,50));

	//create circle shape
	b2CircleShape  circle;
	//circle.m_radius = BALL_RADIUS / PTM_RATIO;
	circle.m_radius = getContentSize().width / 2 / PTM_RATIO;

	//define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.7;

	fixtureDef.filter.categoryBits = ENEMY_AIRCRAFT;
	fixtureDef.filter.maskBits = BOUNDARY | FRIENDLY_AIRCRAFT;
	//_body->SetBullet(true);
	this->initWithFile("enemy.png");

	_body->CreateFixture(&fixtureDef);
	_body->SetUserData(this);

	setSpritePosition(_startPosition);

	_x = _y = true;
}

void Ball::reset() {
	if (_body) {
		_body->SetLinearVelocity(b2Vec2_zero);
		_body->SetAngularVelocity(0);
		_body->SetAwake(true);
	}
	setSpritePosition(_startPosition);
	_inPlay = true;
	setVisible(true);
}

void Ball::update(float dt) {
	b2Vec2 vel = _body->GetLinearVelocity();	
	auto winSize = Director::getInstance()->getWinSize();
	
	auto x = getPosition().x;;
	auto y = getPosition().y;
	
	if (x - getContentSize().width <= 0) _x = true;
	if (x + getContentSize().width >= winSize.width) _x = false;
	if (y - getContentSize().height <= 0) _y = true;
	if (y + getContentSize().height >= winSize.height) _y = false;

	auto speed = 1.0f;
	//if ball's x direction is right
	if (_x == true)
		vel.x = b2Min(vel.x + speed, 5.0f);
	else
		vel.x = b2Max(vel.x - speed, -5.0f);

	//if ball's y direction is up
	if (_y == true)
		vel.y = b2Min(vel.y + speed, 5.0f);
	else
		vel.y= b2Max(vel.y - speed, -5.0f);

	_body->SetLinearVelocity(vel);
}