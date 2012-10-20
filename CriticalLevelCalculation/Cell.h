#ifndef POINT_H_
#define POINT_H_

#include <sstream>

class Cell
{
public:
	unsigned int x, y;
	Cell() : x(0), y(0) {};
	Cell(unsigned int x,unsigned int y) : x(x), y(y) {};
	bool Cell::operator==(const Cell &other) const {
		return (x == other.x) && (y == other.y);
	};
	bool Cell::operator!=(const Cell &other) const {
		return (x != other.x) || (y != other.y);
	};
	bool Cell::operator< (const Cell& other){ 
		return x < other.x && y < other.y;
	};
	std::stringstream dump() {
		std::stringstream ss;
		ss << "[" << x << "," << y << "]";
		return ss;
	};
	size_t hash() const {
		return x << 16 | y;
	}
};

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