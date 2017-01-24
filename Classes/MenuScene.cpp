#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "ItemScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	auto returnButton = MenuItemImage::create("startgame.jpg", "startgame.jpg", CC_CALLBACK_1(MenuScene::changeScene, this));
	auto itemButton = MenuItemImage::create("itembutton.jpg", "itembutton.jpg", CC_CALLBACK_1(MenuScene::itemCallBack, this));
	auto CloseGameButton = MenuItemImage::create("endgame.jpg", "endgame.jpg", CC_CALLBACK_1(MenuScene::CloseGameCallback, this));
	auto menu = Menu::create(returnButton, itemButton, CloseGameButton, NULL);
	menu->setOpacity(180);
	menu->alignItemsVertically();
	menu->setPosition(ccp(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2));
	this->addChild(menu);

	return true;
}

void MenuScene::changeScene(Object *pSender)
{
	auto playScene_change = HelloWorld::createScene();
	TransitionScene * pTran = TransitionFade::create(1.0f, playScene_change);
	Director::getInstance()->replaceScene(pTran);
}

void MenuScene::itemCallBack(Object *pSender)
{
	/*
	int MaxTime = UserDefault::getInstance()->getDoubleForKey("data");
	char str[100];
	sprintf(str, "%d", MaxTime);
	MessageBox(str, "Alert");
	*/

	auto ItemScene_change = ItemScene::createScene();
	TransitionScene * pTran = TransitionFade::create(1.0f, ItemScene_change);
	Director::getInstance()->replaceScene(pTran);
}


void MenuScene::CloseGameCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}