#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "ItemScene.h"
#include "resources.cpp"
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

	//initalize the background
	auto background = Sprite::create(resources::background);
	background->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2);
	addChild(background);
	
	//get Max the point
	double MaxPoint = UserDefault::getInstance()->getDoubleForKey("data");
	char str[100];	sprintf(str, "%.1fs",MaxPoint);

	auto point = Label::createWithSystemFont("", "Ariel", 30);
	point->setColor(Color3B::WHITE);
	point->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height*0.7);
	this->addChild(point);

	point->setString(str);

	//initalize menus
	auto startGameButton = MenuItemImage::create(resources::startgame, resources::startgame, CC_CALLBACK_1(MenuScene::changeScene, this));
	auto CloseGameButton = MenuItemImage::create(resources::endgame, resources::endgame, CC_CALLBACK_1(MenuScene::CloseGameCallback, this));
	auto menu = Menu::create(startGameButton, CloseGameButton, NULL);
	//menu->setOpacity(150);
	menu->alignItemsVertically();
	menu->setPosition(ccp(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height * 0.25));
	this->addChild(menu);

	return true;
}

void MenuScene::changeScene(Object *pSender)
{
	auto playScene_change = HelloWorld::createScene();
	Director::getInstance()->replaceScene(playScene_change);
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
