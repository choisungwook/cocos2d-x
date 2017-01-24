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
	
	int MaxPoint;

	MenuItemImage* Item_1_Button;
	MenuItemImage* Item_2_Button;
	MenuItemImage* Item_3_Button;

	int getItem1 = 0;
	int getItem2 = 0;
	int getItem3 = 0;

	void LoadItem();
	void Iteminit();
	void itemCallBack1(Object *pSender);
	void itemCallBack2(Object *pSender);
	void itemCallBack3(Object *pSender);
	void changeScene(Object *pSender);

	CREATE_FUNC(ItemScene);
};

#endif // __Logo_SCENE_H__
