#include "MenuScene.h"
#include "HelloWorldScene.h"
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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////

	auto logo = Sprite::create("mushroom.png");
	logo->setScale(0.7f);
	logo->setAnchorPoint(Point(0.5, 0.5));
	logo->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(logo);

	auto scene = CallFuncN::create(CC_CALLBACK_1(MenuScene::changeScene, this));
	this->runAction(scene);

	return true;
}

void MenuScene::changeScene(Object *pSender)
{
	auto playScene_change = HelloWorld::createScene();

	TransitionScene * pTran = TransitionFade::create(2.0f, playScene_change);

	Director::getInstance()->replaceScene(pTran);
}
