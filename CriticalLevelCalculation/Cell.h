/*
 * Cell.h
 *
 *      Author: Alex
 */
#ifndef POINT_H_
#define POINT_H_

#include <sstream>
/**
* Class describes cell in Project Space
*/
class Cell
{
public:
	unsigned int x, y;
	Cell() : x(0), y(0) {};
	Cell(unsigned int x,unsigned int y) : x(x), y(y) {};
	/**
	 * Override compare operator
	 */
	bool operator==(const Cell &other) const {
		return (x == other.x) && (y == other.y);
	};
	/**
	 * Override compare operator
	 */
	bool operator!=(const Cell &other) const {
		return (x != other.x) || (y != other.y);
	};
	/**
	 * Override compare operator
	 */
	bool operator< (const Cell& other){ 
		return x < other.x && y < other.y;
	};
	/**
	 * @return Dump current cell for debugging
	 */
	std::stringstream dump() {
		std::stringstream ss;
		ss << "[" << x << "," << y << "]";
		return ss;
	};
	/**
	 * Hash function for using as a key for map @see std::unordered_map
	 */
	size_t hash() const {
		return x << 16 | y;
	}
};

/**
 * Override hash function of the Cell object @see std::unordered_map
 */
namespace std {
	template <>
	class hash<Cell>{
	public :
		size_t operator()(const Cell &cell ) const{
			//return hash<int>()(x.i) ^ hash<int>()(x.j) ^ hash<int>()(x.k);
			return cell.hash();
		}
	};
}


#endif // POINT_H_
