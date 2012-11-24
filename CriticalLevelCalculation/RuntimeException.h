/*
 * RuntimeException.h
 *
 *      Author: Alex
 */

#ifndef RUNTIME_EXCEPTION_H_
#define RUNTIME_EXCEPTION_H_

#include <string>

/**
 * Exception to be thrown in runtime with custom message
 */
struct RuntimeException : public std::exception
{
	/**
	 * Message
	 */
	std::string s;
	/**
	 * Create new exception with message
	 * @param ss
	 */
	RuntimeException(std::string ss) : s(ss) {}
	/**
	 * @return message of the exception
	 */
	const char* what() const throw() { return s.c_str(); }
};

#endif // RUNTIME_EXCEPTION_H_

