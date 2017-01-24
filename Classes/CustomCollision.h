#ifndef __CUSTOMCOLLISION_H__
#define __CUSTOMCOLLISION_H__

#include"cocos2d.h"

USING_NS_CC;

typedef struct tagVertex // 선분
{
	Point start; // 시작점
	Point end;   // 끝점
} Vertex;

class CollisionFunc
{
public:
	static bool collisionCircleToRect(Point circle_pos, float radius, Rect rc);
	// 원과 사각형 충돌
	static bool collisionCircleToAngleRect(Point circle_pos, float radius, Rect rc, float angle);
	// 원과 각도가 돌아가있는 사각형 충돌
	static bool collisionVertexToCircle(Vertex *line, int l_count, Point circle_pos, float radius);
	// 원과 다각형 충돌
	static bool collisionVertexToRect(Vertex *line, int l_count, Rect rc);
	// 다각형과 사각형 충돌+
	static bool collisionVertexToVertex(Vertex *line1, int l_count1, Vertex *line2, int l_count2);
	// 다각형과 다각형 충돌
	static bool collisionLineToCircle(Vertex line, Point circle_pos, float radius);
	// 선과 원 충돌
	static bool collisionLineToRect(Vertex line, Rect rc);
	// 선과 사각형 충돌
	static bool collisionLineToLine(Vertex line1, Vertex line2);
	// 선과 선 충돌
	static bool collisionPointToCircle(Point pos, Point circle_pos, float radius);
	// 점과 원 충돌
	static bool collisionCircleToCircle(Point circle_pos1, float radius1, Point circle_pos2, float radius2);
	// 원과 원 충돌
};

#endif