#include "Sprite_Character.h"
#include "VisibleRect.h"
USING_NS_CC;


MyCharacter* MyCharacter::create(const std::string & filename)
{
	MyCharacter *sprite = new (std::nothrow) MyCharacter();
	//��ΰ� �����ϸ� �ڵ����� ���� �޸� ���� ��� �߰��ϰ� sprite�� ����
	if (sprite && sprite->initWithFile(filename)) {
		sprite->autorelease();		
		return sprite;
	}
	//��ΰ� �������� ������ �����ϰ� �����͸� �����ϰ� null����
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

/*******************************************
Touch Event
********************************************/

MyCharacter::MyCharacter()
{
}

MyCharacter::~MyCharacter()
{
}

bool MyCharacter::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	/*auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);*/
	if (state_Touched) return false;

	pos_TouchBefore = touch->getLocation();
	pos_SpriteBefore = this->getPosition();
	_state = state_Touched;
	return true;
}

void MyCharacter::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto pos_cur = touch->getLocation();
	auto pos_character = this->getPosition();
	float diff_x = pos_cur.x - pos_TouchBefore.x;
	float diff_y = pos_cur.y - pos_TouchBefore.y;

	float x = pos_SpriteBefore.x + diff_x;
	float y = pos_SpriteBefore.y + diff_y;

	//âũ�� �˻�
	if (x > max_x) x = max_x;
	if (x < min_x) x = min_x;
	if (y > max_y) y = max_y;
	if (y < min_y) y = min_y;

	this->setPosition(ccp(x, y));
}

void MyCharacter::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	_state = state_UnTouched;
}

void MyCharacter::onEnter()
{
	Sprite::onEnter();

	//��ġ�̺�Ʈ ���
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MyCharacter::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MyCharacter::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MyCharacter::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//ĳ���Ͱ� ȭ�� ���� �ۿ� ������ ���ϵ��� ...
	float character_width = this->getContentSize().width;
	float character_height = this->getContentSize().height;

	//ĳ���Ͱ� �̵��� �� �ִ� �ּ�,�ִ�ũ��(����� �Ÿ�)
	min_x = 0 + character_width / 2;
	max_x = VisibleRect::getVisibleRect().size.width - character_width / 2;
	min_y = 0 + character_height / 2;
	max_y = VisibleRect::getVisibleRect().size.height - character_height / 2;
}

void MyCharacter::onExit()
{
	Sprite::onExit();
}
