#pragma once

#include <sstream>

using std::istringstream;
using std::string;


class CharSequence
{
	int count;
	istringstream iss;
	char current_char;

public:
	
	bool eof() const;
	int  get_count() const;

	char ch() const;
	void next();

	void str(string&);

	CharSequence(const string&);
	~CharSequence() { }
};