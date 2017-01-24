#pragma once
#ifndef __Item_SCENE_H__
#define __Item_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class ItemScene : public cocos2d::LayerColor
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void itemCallBack1(Object *pSender);
	void itemCallBack2(Object *pSender);
	void itemCallBack3(Object *pSender);
	void changeScene(Object *pSender);

	CREATE_FUNC(ItemScene);
};

#endif // __Logo_SCENE_H__
