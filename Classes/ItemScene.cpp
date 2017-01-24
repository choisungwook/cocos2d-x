#include "ItemScene.h"
#include "MenuScene.h"
#include "VisibleRect.h"
USING_NS_CC;

Scene* ItemScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ItemScene::create();
	scene->addChild(layer);
	return scene;
}

bool ItemScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	auto Item_1_Button = MenuItemImage::create("1.png", "1.png", CC_CALLBACK_1(ItemScene::itemCallBack1, this));
	auto Item_2_Button = MenuItemImage::create("2.png", "2.png", CC_CALLBACK_1(ItemScene::itemCallBack2, this));
	auto Item_3_Button = MenuItemImage::create("3.png", "3.png", CC_CALLBACK_1(ItemScene::itemCallBack3, this));
	auto menu = Menu::create(Item_1_Button, Item_2_Button, Item_3_Button, NULL);
	menu->setOpacity(255);
	menu->alignItemsHorizontally();
	menu->setPosition(ccp(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2));
	this->addChild(menu);

	auto BackButton = MenuItemImage::create("returngame.jpg", "returngame.jpg", CC_CALLBACK_1(ItemScene::changeScene, this));
	auto BackMenu = Menu::create(BackButton, NULL);
	BackMenu->setPosition(ccp(VisibleRect::getVisibleRect().size.width/2, VisibleRect::getVisibleRect().size.height /5));
	this->addChild(BackMenu);

	return true;
}

void ItemScene::changeScene(Object *pSender)
{
	auto playScene_change = MenuScene::createScene();

	TransitionScene * pTran = TransitionFade::create(1.0f, playScene_change);

	Director::getInstance()->replaceScene(pTran);
}

void ItemScene::itemCallBack1(Object *pSender)
{

}
void ItemScene::itemCallBack2(Object *pSender)
{

}
void ItemScene::itemCallBack3(Object *pSender)
{

}