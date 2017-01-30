#include "ItemScene.h"
#include "MenuScene.h"
#include "VisibleRect.h"
#include "resources.cpp"
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

	//initalize the background
	auto background = Sprite::create(resources::background);
	background->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height / 2);
	addChild(background);


	Iteminit();

	//LoadItem();

	MaxPoint = UserDefault::getInstance()->getDoubleForKey("data");
	char str[100];
	sprintf(str, "%s%d", "Maximum : ",MaxPoint);

	auto point = Label::createWithSystemFont("", "Ariel", 20);
	point->setColor(Color3B::ORANGE);
	point->setPosition(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height*0.9);
	this->addChild(point);

	point->setString(str);
		
	//change scene
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

void ItemScene::Iteminit()
{
	Item_1_Button = MenuItemImage::create("1.png", "1.png", CC_CALLBACK_1(ItemScene::itemCallBack1, this));
	Item_2_Button = MenuItemImage::create("2.png", "2.png", CC_CALLBACK_1(ItemScene::itemCallBack2, this));
	//tem_3_Button = MenuItemImage::create("3.png", "3.png", CC_CALLBACK_1(ItemScene::itemCallBack3, this));
	
	auto menu = Menu::create(Item_1_Button, Item_2_Button, NULL);
	menu->alignItemsVertically();
	menu->setPosition(ccp(VisibleRect::getVisibleRect().size.width / 2, VisibleRect::getVisibleRect().size.height * 0.6));
	this->addChild(menu);
}

void ItemScene::LoadItem()
{
	getItem1 = UserDefault::getInstance()->getIntegerForKey("item1");
	getItem2 = UserDefault::getInstance()->getIntegerForKey("item2");
	getItem3 = UserDefault::getInstance()->getIntegerForKey("item3");
	
	if(getItem1 == 1)
		Item_1_Button->setOpacity(255);
	if (getItem2 == 1)
		Item_2_Button->setOpacity(255); 
	if (getItem3 == 1)
		Item_3_Button->setOpacity(255);
}

//buy item
void ItemScene::itemCallBack1(Object *pSender)
{
	if (MaxPoint >= 30 && getItem1 == 0)
	{
		Item_1_Button->setOpacity(255);
		UserDefault::getInstance()->setIntegerForKey("item1", 1);
		UserDefault::getInstance()->flush();
		log("%d", MaxPoint);
	}
}
void ItemScene::itemCallBack2(Object *pSender)
{
	if (MaxPoint >= 50 && getItem2 == 0)
	{
		Item_2_Button->setOpacity(255);
		UserDefault::getInstance()->setIntegerForKey("item2", 1);
		UserDefault::getInstance()->flush();
		log("%d", MaxPoint);
	}
}
void ItemScene::itemCallBack3(Object *pSender)
{
	if (MaxPoint >= 80 && getItem3 == 0)
	{
		Item_3_Button->setOpacity(255);
		UserDefault::getInstance()->setIntegerForKey("item3", 1);
		UserDefault::getInstance()->flush();
		log("%d", MaxPoint);
	}
}