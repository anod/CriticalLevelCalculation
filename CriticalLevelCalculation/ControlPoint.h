/*
 * ControlPoint.h
 *
 *      Author: Alex
 */

#ifndef CONTROL_POINT_H_
#define CONTROL_POINT_H_

/**
 * Certain point in the Project Space with attached timestamp. 
 * It is used for the Flight Path definition.
 * The timestamp defines the moment when this Control Point has to be passed.
 */
struct ControlPoint {
	/**
	 * Control Point time
	 */
	int time;
	/**
	 * Flight coordinate
	 */
	Cell coord;
	/**
	 * Override operator to compare control points
	 */
	inline bool operator< (const ControlPoint& other){ 
		return coord < other.coord;
	};
};

#endif // CONTROL_POINT_H_
