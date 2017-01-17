#ifndef __SPRITE_CHARACTER__
#define __SPRITE_CHARACTER__

#include "cocos2d.h"
#include "Sprite_enemy.h"
USING_NS_CC;

//ĳ���� ���¸� ����
typedef enum tagCharacterState {
	state_Touched, //ĳ���Ͱ� ��ġ�� ����
	state_UnTouched //ĳ���Ͱ� ��ġ���� ���� ����
}CharacterState;

class MyCharacter : public cocos2d::Sprite {
public:
	MyCharacter();
	virtual ~MyCharacter();
	
	//touch event
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);		

	//Rect
	Rect collisionRegion();

	//����� �浹üũ
	bool collisionWithEnemy(Enemy* enemy);


	//Life cycles
	virtual void onEnter() override;
	virtual void onExit() override;

	//sprite �����ؼ� �ּҸ� ����
	static MyCharacter* create(const std::string& filename);

private:
	CharacterState _state;
	cocos2d::Vec2 pos_TouchBefore;
	cocos2d::Vec2 pos_SpriteBefore;

	//ĳ���� ũ�� 
	float min_x;
	float min_y;
	float max_x;
	float max_y;
};

#endif
