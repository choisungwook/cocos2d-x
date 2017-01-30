#pragma once
#ifndef __Menu_SCENE_H__
#define __Menu_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public cocos2d::LayerColor
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void changeScene(Object *pSender);
	void CloseGameCallback(Ref* pSender);

	CREATE_FUNC(MenuScene);
};

#endif // __Logo_SCENE_H__
