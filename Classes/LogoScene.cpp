#include "LogoScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* Logo::createScene()
{
	auto scene = Scene::create();
	auto layer = Logo::create();
	scene->addChild(layer);
	return scene;
}

bool Logo::init()
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

	auto scene = CallFuncN::create(CC_CALLBACK_1(Logo::changeScene, this));
	this->runAction(scene);

	return true;
}

void Logo::changeScene(Object *pSender)
{
	auto logo_change = HelloWorld::createScene();

	TransitionScene * pTran = TransitionFade::create(5.0f, logo_change);

	Director::getInstance()->replaceScene(pTran);
}
