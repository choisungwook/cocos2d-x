#include "Sprite_Character.h"
#include "VisibleRect.h"
#include "CustomCollision.h"
USING_NS_CC;

MyCharacter* MyCharacter::create(const std::string & filename)
{
	MyCharacter *sprite = new (std::nothrow) MyCharacter();
	//경로가 존재하면 자동으로 동적 메모리 제거 기능 추가하고 sprite를 리턴
	if (sprite && sprite->initWithFile(filename)) {
		sprite->set_radius(sprite->getContentSize().width / 2);
		sprite->autorelease();		
		return sprite;
	}
	//경로가 존재하지 않으면 안전하게 포인터를 제거하고 null리턴
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

MyCharacter::MyCharacter()
{
}

MyCharacter::~MyCharacter()
{
}

//적들과 충돌체크
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
}

void MyCharacter::onExit()
{
	Sprite::onExit();
}
