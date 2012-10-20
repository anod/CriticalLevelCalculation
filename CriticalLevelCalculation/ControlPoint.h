#ifndef CONTROL_POINT_H_
#define CONTROL_POINT_H_

struct ControlPoint {
	Point coord;
	int flight;
	inline bool operator< (const ControlPoint& other){ 
		return coord < other.coord;
	};
};

#endif // CONTROL_POINT_H_