#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Sprite_Character.h"
#include "Sprite_enemy.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
	void startGame(float dt);
	void gameLogic(float dt);

	// touch events
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// initalize functions
	void initalizeBackground();
	void initalizeCharacter();
	void initalizeMenu();
	void initalizeTimer();
	void initializItem();
	void initializeEnemy(float dt);
	
	void OptionCallback(Ref* pSender);
	void CloseGameCallback(Ref* pSender);
	void ReturnGameCallback(Ref* pSender);
	void ReturnScene(Ref* pSender);
	void EatItemCallback(Ref* pSender);
		
	void UpdateTimer(float dt);
	void EatTimer(float dt);

	//data save & road
	int getItem1;
	int getItem2;
	int getItem3;
	void SaveData();
	void LoadData();	

private:
	MyCharacter* sprite_Character;
	cocos2d::Vec2 pos_TouchBefore;
	cocos2d::Vec2 pos_SpriteBefore;
	cocos2d::Vector<Enemy*> vector_enemies;
	cocos2d::Sprite* background;
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//Item
	cocos2d::MenuItemImage* eatItem;

	//timer
	double chkTime = 0;
	double EatTime = 3.0f;
	Label* timerLabel;
	Label* eattimerLabel;

	//Option Layer
	cocos2d::Layer* OptionLayer = NULL;

	//state
	bool isPause = false;

	//Option Layer
	cocos2d::Layer* ItemLayer = NULL;

	// about character 
	float min_x;
	float min_y;
	float max_x;
	float max_y;

	// data
	int MaxTime = 0;

};

#endif // __HELLOWORLD_SCENE_H__