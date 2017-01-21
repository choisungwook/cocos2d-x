#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "ball.h"
#include "character.h"
#include "GLES-Render.h"
USING_NS_CC;

enum _entityCategory {
	BOUNDARY = 0x0001,
	FRIENDLY_SHIP = 0x0002,
	ENEMY_SHIP = 0x0004,
	FRIENDLY_AIRCRAFT = 0x0008,
	ENEMY_AIRCRAFT = 0x0010,
};


class HelloWorld : public cocos2d::LayerColor
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
	CC_SYNTHESIZE(b2World *, _world, World);

    static cocos2d::Scene* createScene();

    virtual bool init();
	
	void initPhysics();
	void update(float dt);
	void initializeEnemy(float dt);
	void addWall(float w, float h, float px, float py);
	

	virtual bool onTouchBegan(Touch * touch, Event * event);
	virtual void onTouchMoved(Touch * touch, Event * event);
	virtual void onTouchEnded(Touch * touch, Event * event);
	//virtual void draw(Renderer *renderer, const Mat4 &transform,	uint32_t flags) override;

	void logic(float dt);


private:
	Size _screenSize;
	Vector<Ball *> _balls;
	Character* character;
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	Vec2 previousPos;
	Vec2 previousSpritePos;
	//캐릭터 크기 
	float min_x;
	float min_y;
	float max_x;
	float max_y;




	GLESDebugDraw * _debugDraw;
	Mat4 _modelViewMV;
	//void onDraw();
	CustomCommand _customCommand;
};

#endif // __HELLOWORLD_SCENE_H__
