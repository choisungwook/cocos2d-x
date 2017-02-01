#include "Gameover.h"
#include "resources.h"
#include "VisibleRect.h"
#include "MenuScene.h"
#include "HelloWorldScene.h"

double currentTime;

cocos2d::Scene * GameOverScene::createScene(double currentTimePoint)
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);

	currentTime = currentTimePoint;
	return scene;
}

bool GameOverScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
	{
		return false;
	}

	//initalize the background
	auto sbackground = Sprite::create(background);
	sbackground->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2);
	addChild(sbackground);

	//initalize menus
	auto goMenuButton = MenuItemImage::create(home, home, CC_CALLBACK_1(GameOverScene::changeMenuScene, this));
	auto startGameButton = MenuItemImage::create(startgame, startgame, CC_CALLBACK_1(GameOverScene::changeGameScene, this));
	auto CloseGameButton = MenuItemImage::create(endgame, endgame, CC_CALLBACK_1(GameOverScene::CloseGameCallback, this));
	auto menu = Menu::create(goMenuButton, startGameButton, CloseGameButton, NULL);
	//menu->setOpacity(150);
	menu->alignItemsHorizontally();
	menu->setPosition(ccp(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height * 0.25));
	this->addChild(menu);

	return true;
}

void GameOverScene::onEnter()
{
	LayerColor::onEnter();

	//current Point
	auto Curpoint = Label::createWithSystemFont("", "Ariel", 30);
	Curpoint->setColor(Color3B::WHITE);
	Curpoint->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height*0.7);
	Curpoint->setString(StringUtils::format("this game's time %.1f", currentTime));
	this->addChild(Curpoint);
	
	//get Max the point
	double MaxPoint = LoadPoint();
	auto point = Label::createWithSystemFont("", "Ariel", 20);
	point->setColor(Color3B::WHITE);
	point->setString(StringUtils::format("your max time %.1f", MaxPoint));
	point->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height*0.55);
	this->addChild(point);

	//check and save Point
	SavePoint();
}

void GameOverScene::onExit()
{
	LayerColor::onExit();
}

void GameOverScene::changeMenuScene(Object * pSender)
{
	auto playScene_change = MenuScene::createScene();
	TransitionScene * pTran = TransitionFade::create(1.0f, playScene_change);
	Director::getInstance()->replaceScene(pTran);
}

void GameOverScene::changeGameScene(Object * pSender)
{
	auto playScene_change = HelloWorld::createScene();
	TransitionScene * pTran = TransitionFade::create(0.5f, playScene_change);
	Director::getInstance()->replaceScene(pTran);
}

void GameOverScene::CloseGameCallback(Ref * pSender)
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

void GameOverScene::SavePoint()
{
	//if the current Point is bigger than max Point, it would change theses
	if (LoadPoint() < currentTime)
	{
		UserDefault::getInstance()->setDoubleForKey("data", currentTime);
		UserDefault::getInstance()->flush();
	}
}

double GameOverScene::LoadPoint()
{
	return UserDefault::getInstance()->getDoubleForKey("data");
}

