#ifndef __Logo_SCENE_H__
#define __Logo_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Logo : public cocos2d::LayerColor
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void changeScene(Object *pSender);

	CREATE_FUNC(Logo);
};

#endif // __Logo_SCENE_H__
