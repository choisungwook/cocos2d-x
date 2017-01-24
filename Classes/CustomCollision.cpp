#include "CustomCollision.h"

bool CollisionFunc::collisionCircleToRect(Point circle_pos, float radius, Rect rc)
{
	float cx, cy;
	cx = circle_pos.x;
	cy = circle_pos.y;

	if ((rc.getMinX() - radius <= cx && cx <= rc.getMaxX() + radius) ||
		(rc.getMaxY() + radius <= cy && cy <= rc.getMinY() - radius))
	{
		Rect _rc = Rect(
			rc.getMinX() - radius,
			rc.getMinY() - radius,
			rc.size.width + radius * 2,
			rc.size.height + radius * 2);
		if ((_rc.getMinX() < cx && cx < _rc.getMaxX()) &&
			(_rc.getMinY() < cy && cy < _rc.getMaxY()))
		{
			return true;
		}
	}
	else
	{
		if (collisionPointToCircle(Point(rc.getMinX(), rc.getMaxY()), circle_pos, radius))
			return true;
		if (collisionPointToCircle(Point(rc.getMinX(), rc.getMinY()), circle_pos, radius))
			return true;
		if (collisionPointToCircle(Point(rc.getMaxX(), rc.getMaxY()), circle_pos, radius))
			return true;
		if (collisionPointToCircle(Point(rc.getMaxX(), rc.getMinY()), circle_pos, radius))
			return true;
	}
	return false;
}

bool CollisionFunc::collisionCircleToAngleRect(Point circle_pos, float radius, Rect rc, float angle)
{
	angle = CC_DEGREES_TO_RADIANS(angle);
	float tx = cosf(angle) * (circle_pos.x - rc.getMidX()) + sinf(angle) * -1 * (circle_pos.y - rc.getMidY());
	float ty = sinf(angle) * (circle_pos.x - rc.getMidX()) + cosf(angle) * (circle_pos.y - rc.getMidY());
	circle_pos = Point(tx, ty);

	rc = Rect(-rc.size.width / 2, -rc.size.height / 2, rc.size.width, rc.size.height);

	return CollisionFunc::collisionCircleToRect(circle_pos, radius, rc);
}

bool CollisionFunc::collisionVertexToCircle(Vertex *line, int l_count, Point circle_pos, float radius)
{
	for (int i = 0; i < l_count; i++)
		if (collisionLineToCircle(line[i], circle_pos, radius))
			return true;
	return false;
}

bool CollisionFunc::collisionVertexToRect(Vertex *line, int l_count, Rect rc)
{
	for (int i = 0; i < l_count; i++)
	{
		if (collisionLineToRect(line[i], rc))
			return true;
	}
	return false;
}

bool CollisionFunc::collisionVertexToVertex(Vertex *line1, int l_count1, Vertex *line2, int l_count2)
{
	for (int i = 0; i< l_count1; i++)
	{
		for (int j = 0; j< l_count2; j++)
		{
			if (collisionLineToLine(line1[i], line2[j]))
				return true;
		}
	}
	return false;
}

bool CollisionFunc::collisionLineToCircle(Vertex line, Point circle_pos, float radius)
{
	float cx = circle_pos.x;
	float cy = circle_pos.y;

	if (line.start.x != line.end.x)
	{
		float c = (line.end.y - line.start.y) / (line.end.x - line.start.x);
		float d = line.end.y - c * line.end.x;
		float e = d - cy;
		float D = pow(c * e - cx, 2) - (pow(c, 2) + 1) * (pow(cx, 2) + pow(e, 2) - pow(radius, 2));
		if (D >= 0 &&
			(cx - c*e + sqrtf(D)) / ((pow(c, 2) + 1)) >= MIN(line.start.x, line.end.x) &&
			(cx - c*e - sqrtf(D)) / ((pow(c, 2) + 1)) <= MAX(line.start.x, line.end.x))
		{
			return true;
		}
	}
	else
	{
		float l = line.start.x;
		float D = pow(cy, 2) - pow(l - cx, 2) - pow(cy, 2) + pow(radius, 2);
		if (D >= 0 &&
			cy + sqrtf(D) >= MIN(line.start.y, line.end.y) &&
			cy - sqrtf(D) <= MAX(line.start.y, line.end.y))
		{
			return true;
		}
	}
	return false;
}

bool CollisionFunc::collisionLineToRect(Vertex line, Rect rc)
{
	Vertex rectVertex[4];

	rectVertex[0].start = Point(rc.getMinX(), rc.getMaxY());
	rectVertex[0].end = Point(rc.getMaxX(), rc.getMaxY());

	rectVertex[1].start = Point(rc.getMinX(), rc.getMaxY());
	rectVertex[1].end = Point(rc.getMaxX(), rc.getMaxY());

	rectVertex[2].start = Point(rc.getMinX(), rc.getMinY());
	rectVertex[2].end = Point(rc.getMinX(), rc.getMaxY());

	rectVertex[3].start = Point(rc.getMaxX(), rc.getMinY());
	rectVertex[3].end = Point(rc.getMaxX(), rc.getMaxY());

	for (int i = 0; i< 4; i++)
	{
		if (collisionLineToLine(line, rectVertex[i]))
			return true;
	}
	return false;
}

bool CollisionFunc::collisionLineToLine(Vertex line1, Vertex line2)
{
	Point s1 = line1.start, e1 = line1.end;
	Point s2 = line2.start, e2 = line2.end;

	if (s1.x != e1.x && s2.x != e2.x)
	{
		float c1 = (e1.y - s1.y) / (e1.x - s1.x);
		float c2 = (e2.y - s2.y) / (e2.x - s2.x);
		float d1 = e1.y - c1 * e1.x;
		float d2 = e2.y - c2 * e2.x;

		float x = (d2 - d1) / (c1 - c2);
		float y = c1 * x + d1;

		if (x >= MIN(line1.start.x, line1.end.x) &&
			x >= MIN(line2.start.x, line2.end.x) &&
			x <= MAX(line1.start.x, line1.end.x) &&
			x <= MAX(line2.start.x, line2.end.x))
		{
			return true;
		}
	}
	else if (s1.x == e1.x && s2.x == e2.x)
	{
		if (s1.x == s2.x)
			return true;
	}
	else
	{
		//2번쨰가 직선
		if (s1.x == e1.x)
		{
			Point temp;
			temp = s1;
			s1 = s2;
			s2 = temp;

			temp = e1;
			e1 = e2;
			e2 = temp;
		}

		float c1 = (e1.y - s1.y) / (e1.x - s1.x);
		float d1 = e1.y - c1 * e1.x;

		float x = e2.x;
		float y = c1 * x + d1;

		if (y >= MIN(s2.y, e2.y) &&
			y <= MAX(s2.y, e2.y) &&
			x >= MIN(s1.x, e1.x) &&
			x <= MAX(s1.x, e1.x))
			return true;
	}
	return false;
}

bool CollisionFunc::collisionPointToCircle(Point pos, Point circle_pos, float radius)
{
	float deltaX = circle_pos.x - pos.x;

	float deltaY = circle_pos.y - pos.y;

	float length = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (length > radius)
		return false;

	return true;
}

bool CollisionFunc::collisionCircleToCircle(Point circle_pos1, float radius1, Point circle_pos2, float radius2)
{
	if (radius1 + radius2 >
		sqrtf(pow(circle_pos1.x - circle_pos2.x, 2) + pow(circle_pos1.y - circle_pos2.y, 2)))
	{
		return true;
	}
	return false;
}