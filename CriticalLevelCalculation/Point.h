#ifndef POINT_H_
#define POINT_H_

#include <sstream>

class Point
{
public:
	int x, y;
	Point() : x(0), y(0) {};
	Point(int x, int y) : x(x), y(y) {};
	bool Point::operator==(const Point &other) const {
		return (x == other.x) && (y == other.y);
	};
	bool Point::operator!=(const Point &other) const {
		return (x != other.x) || (y != other.y);
	};
	bool Point::operator< (const Point& other){ 
		return x < other.x && y < other.y;
	};
	std::stringstream dump() {
		std::stringstream ss;
		ss << "[" << x << "," << y << "]";
		return ss;
	};
};

#endif // POINT_H_