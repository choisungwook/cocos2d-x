#pragma once
#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOverScene : public cocos2d::LayerColor
{
public:

	static cocos2d::Scene* createScene(double currentTimePoint);

	virtual bool init();

	//Life cycles
	virtual void onEnter() override;
	virtual void onExit() override;

	void changeMenuScene(Object *pSender);
	void changeGameScene(Object *pSender);
	void CloseGameCallback(Ref* pSender);

	void SavePoint();
	double LoadPoint();

	CREATE_FUNC(GameOverScene);
};

#endif // __Logo_SCENE_H__
