#ifndef __MiniPool__b2Sprite__
#define __MiniPool__b2Sprite__

#define PTM_RATIO 32.0
#define BALL_RADIUS 10.0

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class HelloWorld;

enum {
    kSpritePlayer,
    kSpriteBall,
    kSpriteCue,
    kSpritePocket
};

using namespace cocos2d;

class b2Sprite : public Sprite {
    
public:    
	b2Sprite(HelloWorld * game) { _game = game; };

    CC_SYNTHESIZE(b2Body *, _body, Body);
	CC_SYNTHESIZE(HelloWorld *, _game, Game);

    virtual void setSpritePosition (Point position);
    virtual void update(float dt);
    virtual void hide(void);
    virtual void reset(void);
    virtual float mag();
};


#endif /* defined(__MiniPool__b2Sprite__) */
