#ifndef __BALL_H__
#define __BALL_H__
#include "b2Sprite.h"

enum {
	kColorYellow,
	kColorRed,
	kColorBlack,
	kColorWhite

};

class Ball : public b2Sprite {

public:

	CC_SYNTHESIZE(bool, _inPlay, InPlay);

	virtual ~Ball();
	Ball(HelloWorld * game, Point position, int color);
	static Ball* create(HelloWorld * game, Point position, int color);
	virtual void reset(void);
	virtual void update(float dt);
private:
	void initBall();
	Point _startPosition;

	int _color;

	//direction values
	bool _y; //if it is true, the ball's direction is up
	bool _x; //if it is true, the ball's direction is left

};

#endif /* defined(__MiniPool__Ball__) */
