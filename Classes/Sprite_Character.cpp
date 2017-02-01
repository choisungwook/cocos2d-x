#include "Sprite_Character.h"
#include "VisibleRect.h"
#include "CustomCollision.h"
#include "resources.h"
USING_NS_CC;

MyCharacter* MyCharacter::create(const std::string & filename)
{
	MyCharacter *sprite = new (std::nothrow) MyCharacter();
	//��ΰ� �����ϸ� �ڵ����� ���� �޸� ���� ��� �߰��ϰ� sprite�� ����
	if (sprite && sprite->initWithFile(filename)) {
		sprite->set_radius(sprite->getContentSize().width / 2);
		sprite->setZOrder(characterOrder);
		sprite->autorelease();		
		return sprite;
	}
	//��ΰ� �������� ������ �����ϰ� �����͸� �����ϰ� null����
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

MyCharacter::MyCharacter()
{
}

MyCharacter::~MyCharacter()
{
}

//����� �浹üũ
bool MyCharacter::collisionWithEnemy(Enemy* enemy)
{
	Point srcPos = { getPosition().x, getPosition().y };
	float srcRadius = getContentSize().width / 2 ;
	
	Point dstPos = { enemy->getPosition().x, enemy->getPosition().y };
	float dstRadius = enemy->get_radius();

	bool collision = CollisionFunc::collisionCircleToCircle(srcPos, radius, dstPos, dstRadius);

	if (collision) {
		return true;
	}

	return false;
}

void MyCharacter::onEnter()
{
	Sprite::onEnter();

	_state = state_Standard;
}

void MyCharacter::onExit()
{
	Sprite::onExit();
}
