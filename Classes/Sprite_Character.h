#ifndef __SPRITE_CHARACTER__
#define __SPRITE_CHARACTER__

#include "cocos2d.h"

//캐릭터 상태를 저장
typedef enum tagCharacterState {
	state_Touched, //캐릭터가 터치된 상태
	state_UnTouched //캐릭터가 터치되지 않은 상태
}CharacterState;

class MyCharacter : public cocos2d::Sprite {
public:
	MyCharacter();
	virtual ~MyCharacter();
	
	//touch event
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);		

	//Life cycles
	virtual void onEnter() override;
	virtual void onExit() override;

	//sprite 생성해서 주소를 리턴
	static MyCharacter* create(const std::string& filename);

private:
	CharacterState _state;
	cocos2d::Vec2 pos_TouchBefore;
	cocos2d::Vec2 pos_SpriteBefore;

	//캐릭터 크기 
	float min_x;
	float min_y;
	float max_x;
	float max_y;
};

#endif
