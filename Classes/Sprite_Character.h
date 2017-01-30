#ifndef __SPRITE_CHARACTER__
#define __SPRITE_CHARACTER__

#include "cocos2d.h"
#include "Sprite_enemy.h"
USING_NS_CC;

//캐릭터 상태를 저장
typedef enum tagCharacterState {
	state_Touched, //캐릭터가 터치된 상태
	state_UnTouched, //캐릭터가 터치되지 않은 상태
	state_Standard,
	state_Eat,
}CharacterState;

class MyCharacter : public cocos2d::Sprite {
public:
	MyCharacter();
	virtual ~MyCharacter();
	
	//check collide the enemies
	bool collisionWithEnemy(Enemy* enemy);
	//gettter, setter raduis
	CC_SYNTHESIZE(float, radius, _radius);
	CC_SYNTHESIZE(CharacterState, _state, state);

	//Life cycles
	virtual void onEnter() override;
	virtual void onExit() override;

	static MyCharacter* create(const std::string& filename);

private:
	cocos2d::Vec2 pos_TouchBefore;
	cocos2d::Vec2 pos_SpriteBefore;
};

#endif
