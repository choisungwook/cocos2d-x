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

	//게임 흐름에 관련된 함수	
	void startGame(float dt);
	void gameLogic(float dt);
	bool isPlaying;

	//터치 이벤트 관련 함수
	virtual bool onTouch(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	//캐릭터 관련 함수
	void initalizeCharacter();

	//test Option Layer
	cocos2d::Layer* OptionLayer = NULL;
	cocos2d::Sprite* rect;
	bool isPause = false;
	void initalizeMenu();
	void ButtonCallback(Ref* pSender);
	void OptionCallback(Ref* pSender);
	void CloseGameCallback(Ref* pSender);
	void ReturnGameCallback(Ref* pSender);

	//적(총알역할) 관련 함수 & 변수
	void initializeEnemy(float dt);
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

private:
	MyCharacter* sprite_Character; //게임캐릭터
	cocos2d::Vec2 pos_TouchBefore;
	cocos2d::Vec2 pos_SpriteBefore;
	cocos2d::Vector<Enemy*> vector_enemies;
};

#endif // __HELLOWORLD_SCENE_H__

