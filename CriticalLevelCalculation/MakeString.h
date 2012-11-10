#ifndef MAKE_STRING_H_
#define MAKE_STRING_H_

class MakeString
{
public:
	std::stringstream stream;
	operator std::string() const { return stream.str(); }

	template<class T>
	MakeString& operator<<(T const& VAR) { stream << VAR; return *this; }
};

#endif //MAKE_STRING_H_