#include "StdAfx.h"
#include "CharSequence.h"

using std::string;
using std::istringstream;

CharSequence::CharSequence(const string& istr) : iss(istr), count(0)
{	
	next();
}

void CharSequence::next() 
{
	if (!iss.eof())
	{
		++count;
		iss.get(current_char);
	}
	else
		current_char = '$';
}

bool CharSequence::eof() const
{
	return iss.eof();
}

int CharSequence::get_count() const
{
	return count;
}

char CharSequence::ch() const
{
	return current_char;
}

void CharSequence::str(string& s)
{
	count = 0;
	iss.clear();	
	iss.str(s);
	next();
}