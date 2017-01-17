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
	//��ΰ� �����ϸ� �ڵ����� ���� �޸� ���� ��� �߰��ϰ� sprite�� ����
	if (sprite && sprite->initWithFile(filename)) {
		sprite->autorelease();
		return sprite;
	}
	//��ΰ� �������� ������ �����ϰ� �����͸� �����ϰ� null����
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

//�� ������
void Enemy::move()
{	
	this->setPosition(getPosition() + velocity);

	//x�� �˻�
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
	//y�� �˻�
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
