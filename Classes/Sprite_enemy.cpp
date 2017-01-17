#include "Sprite_enemy.h"
#include "VisibleRect.h"
USING_NS_CC;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

Enemy * Enemy::create(const std::string & filename)
{
	Enemy *sprite = new (std::nothrow) Enemy();
	//경로가 존재하면 자동으로 동적 메모리 제거 기능 추가하고 sprite를 리턴
	if (sprite && sprite->initWithFile(filename)) {
		sprite->autorelease();
		return sprite;
	}
	//경로가 존재하지 않으면 안전하게 포인터를 제거하고 null리턴
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

//공 움직임
void Enemy::move()
{	
	this->setPosition(getPosition() + velocity);

	//x축 검사
	if (getPosition().x > VisibleRect::right().x - radius())
	{
		setPosition(VisibleRect::right().x - radius(), getPosition().y);
		velocity.x *= -1;
	}
	else if (getPosition().x < VisibleRect::left().x + radius())
	{
		setPosition(VisibleRect::left().x + radius(), getPosition().y);
		velocity.x *= -1;
	}
	//y축 검사
	if (getPosition().y > VisibleRect::top().y - radius())
	{
		setPosition(getPosition().x, VisibleRect::top().y - radius());
		velocity.y *= -1;
	}
	else if (getPosition().y < VisibleRect::bottom().y + radius())
	{
		setPosition(getPosition().x, VisibleRect::bottom().y + radius());
		velocity.y *= -1;
	}
}

float Enemy::radius()
{
	return getTexture()->getContentSize().width / 2;	
}

void Enemy::onEnter()
{
	//log("radius : %f ", radius());
	Sprite::onEnter();
}

void Enemy::onExit()
{
	Sprite::onExit();
}
