/*
 * MakeString.h
 *
 *      Author: Alex
 */

#ifndef MAKE_STRING_H_
#define MAKE_STRING_H_

/**
 * Facility to create inline strings using stream format
 * Usage:
 *  std::string result = MakeString() << "A" << "B";
 */
class MakeString
{
public:
	/**
	 * stream to append the string
	 */
	std::stringstream stream;
	/**
	 * return current string
	 */
	operator std::string() const { return stream.str(); }

	/**
	 * appends VAR to stream
	 * @param VAR
	 * @return
	 */
	template<class T>
	MakeString& operator<<(T const& VAR) { stream << VAR; return *this; }
};

#endif //MAKE_STRING_H_
