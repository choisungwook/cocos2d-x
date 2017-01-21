#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "b2Sprite.h"

class Character : public b2Sprite {

public:

	CC_SYNTHESIZE(bool, _inPlay, InPlay);

	virtual ~Character();
	Character(HelloWorld * game, Point position, int color);
	static Character* create(HelloWorld * game, Point position, int color);
	virtual void reset(void);
	virtual void update(float dt);
private:
	void initCharacter();
	Point _startPosition;

	int _color;

};

#endif /* defined(__MiniPool__Ball__) */
