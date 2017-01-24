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
	bool isPlaying;

	// touch events
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// initalize functions
	void initalizeCharacter();
	void initalizeMenu();


	//test Option Layer
	cocos2d::Layer* OptionLayer = NULL;
	cocos2d::Sprite* rect;
	bool isPause = false;

	void ButtonCallback(Ref* pSender);
	void Button1Callback(Ref* pSender);
	void Button2Callback(Ref* pSender);
	void Button3Callback(Ref* pSender);

	void OptionCallback(Ref* pSender);
	void CloseGameCallback(Ref* pSender);
	void ReturnGameCallback(Ref* pSender);
	void ReturnScene(Ref* pSender);

	//timer
	double chkTime = 0;
	Label* timerLabel;
	void initTimer();
	void UpdateTimer(float dt);

	//data save & road
	int getItem1;
	int getItem2;
	int getItem3;
	void SaveData();
	void LoadData();
	
	//적(총알역할) 관련 함수 & 변수
	void initializeEnemy(float dt);
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

private:
	MyCharacter* sprite_Character;
	cocos2d::Vec2 pos_TouchBefore;
	cocos2d::Vec2 pos_SpriteBefore;
	cocos2d::Vector<Enemy*> vector_enemies;
	cocos2d::Sprite* background;

	// about character 
	float min_x;
	float min_y;
	float max_x;
	float max_y;

	// data
	int MaxTime = 0;

};

#endif // __HELLOWORLD_SCENE_H__