#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

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
	void moveCharacter();	
	void initalizeCharacter();

	//Item Menu Layer
	void initializeButtonLayer();

	//적(총알역할) 관련 함수 & 변수
	void initializeEnemy(float dt);
	std::vector<std::pair<cocos2d::Sprite*, cocos2d::Point> > vecEnemy; //sprite, Point(movement x, movement y)
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

private:
	cocos2d::Sprite* sprite_AnimationCharacter;
	cocos2d::Sprite* sprite_Character;
	cocos2d::Vec2 pos_TouchBefore;
	cocos2d::Vec2 pos_SpriteBefore;

	//캐릭터 관련된 변수
	float min_x;
	float min_y;
	float max_x;
	float max_y;
};

#endif // __HELLOWORLD_SCENE_H__

