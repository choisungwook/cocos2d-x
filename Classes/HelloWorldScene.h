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

	//���� �帧�� ���õ� �Լ�	
	void startGame(float dt);
	void gameLogic(float dt);
	bool isPlaying;

	//��ġ �̺�Ʈ ���� �Լ�
	virtual bool onTouch(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	//ĳ���� ���� �Լ�
	void initalizeCharacter();

	//test
	void ButtonCallback(Ref* pSender);

	//��(�Ѿ˿���) ���� �Լ� & ����
	void initializeEnemy(float dt);
	std::vector<std::pair<cocos2d::Sprite*, cocos2d::Point> > vecEnemy; //sprite, Point(movement x, movement y)
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

private:
	cocos2d::Sprite* sprite_Character; //����ĳ����
	cocos2d::Vec2 pos_TouchBefore;
	cocos2d::Vec2 pos_SpriteBefore;
	cocos2d::Vector<Enemy*> vector_enemies;
};

#endif // __HELLOWORLD_SCENE_H__

