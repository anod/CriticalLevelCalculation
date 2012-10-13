#ifndef RUNTIME_EXCEPTION_H_
#define RUNTIME_EXCEPTION_H_

struct RuntimeException : public std::exception
{
	std::string s;
	RuntimeException(std::string ss) : s(ss) {}
	const char* what() const throw() { return s.c_str(); }
};

#endif // RUNTIME_EXCEPTION_H_

