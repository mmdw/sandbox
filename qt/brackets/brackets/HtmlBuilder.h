#pragma once
#include "Parser.h"
#include <string>

using std::string;

class HtmlBuilder :	public Parser 
{
	void parse_beg();
	void parse_end();

	void parse_read_ch();
	void parse_empty_char();

	void parse_read_S_beg();
	void parse_read_S_end();

	void parse_read_S_round_beg();
	void parse_read_S_round_end();

	void parse_read_S_square_beg();
	void parse_read_S_square_end();

	string html;
	bool valid;
	
public:
	HtmlBuilder(const string&);
	string getHtml() const;
	bool isValid() const {return valid;}
	~HtmlBuilder(void) { }
};
