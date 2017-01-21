#include "character.h"
#include "HelloWorldScene.h"

Character::~Character() {
}

Character::Character(HelloWorld * game, Point position, int color) : b2Sprite(game) {
	_startPosition = position;
	_color = color;
	_inPlay = true;
}

Character* Character::create(HelloWorld * game, Point position, int color) {
	auto sprite = new Character(game, position, color);
	if (sprite) {
		sprite->initCharacter();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Character::initCharacter() {

	//create box2d body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	_body = _game->getWorld()->CreateBody(&bodyDef);
	_body->SetSleepingAllowed(true);
	_body->SetLinearDamping(1.2);
	_body->SetAngularDamping(0.8);

	this->initWithFile("1.png");

	//create circle shape
	b2CircleShape  circle;
	//circle.m_radius = BALL_RADIUS / PTM_RATIO;
	circle.m_radius = (getContentSize().width / 2) / PTM_RATIO;

	//define fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 5;
	fixtureDef.restitution = 0.7;

	fixtureDef.filter.categoryBits = 0x0010;
	fixtureDef.filter.maskBits = 0xFFFF;
	//_body->SetBullet(true);
	

	_body->CreateFixture(&fixtureDef);
	_body->SetUserData(this);

	setSpritePosition(_startPosition);
}

void Character::reset() {
	if (_body) {
		_body->SetLinearVelocity(b2Vec2_zero);
		_body->SetAngularVelocity(0);
		_body->SetAwake(true);
	}
	setSpritePosition(_startPosition);
	_inPlay = true;
	setVisible(true);
}

void Character::update(float dt) {

	/*if (_body && isVisible()) {
	setPositionX(_body->GetPosition().x * PTM_RATIO);
	setPositionY(_body->GetPosition().y * PTM_RATIO);
	}*/

	/*setPositionX(_body->GetPosition().x * PTM_RATIO);
	setPositionY(_body->GetPosition().y * PTM_RATIO);*/

	//float angle = _body->GetAngle();
	float angle = _body->GetAngle();
	float speed = 0.01;
	_body->ApplyLinearImpulse(b2Vec2(sin(angle) * speed * PTM_RATIO, cos(angle) * speed * PTM_RATIO), _body->GetPosition(), true);

}