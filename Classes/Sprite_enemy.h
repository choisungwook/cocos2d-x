#ifndef __SPRITE_ENEMY__
#define __SPRITE_ENEMY__

#include "cocos2d.h"
USING_NS_CC;

class Enemy : public cocos2d::Sprite {
public:
	Enemy();
	virtual ~Enemy();

	static Enemy* create(const std::string & filename);

	void move(); // 이동
	float radius(); //반지름 계산

	virtual void onEnter() override;
	virtual void onExit() override;

	//getter, setter
	Vec2 getvelocity() { return velocity; };
	void setvelocity(Vec2 Velocity) { velocity = Velocity; };

private:
	Vec2 velocity;
};


#endif
