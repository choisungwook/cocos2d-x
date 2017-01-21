#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "ball.h"

#include "GLES-Render.h"
USING_NS_CC;


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
	void addWall(float w, float h, float px, float py);

	virtual void draw(Renderer *renderer, const Mat4 &transform,
		uint32_t flags) override;

private:

	Size _screenSize;
	Vector<Ball *> _balls;

	GLESDebugDraw * _debugDraw;
	Mat4 _modelViewMV;
	void onDraw();
	CustomCommand _customCommand;
};

#endif // __HELLOWORLD_SCENE_H__
