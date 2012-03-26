#pragma once

#include <sstream>
#include <string>
#include "CharSequence.h"

using std::string;

class Parser
{
protected:
	char ch;	

private:
	void error(const string&);

	void read_S();
	void read_S_square();
	void read_S_round();	
	void read_ch();

	bool valid;

	string err_msg;
	int err_pos;

	CharSequence chSeq;

	virtual void parse_beg()  {}
	virtual void parse_end()  {}

	virtual void parse_read_ch() {}
	virtual void parse_empty_char() {}

	virtual void parse_read_S_beg() {}
	virtual void parse_read_S_end() {}

	virtual void parse_read_S_round_beg() {}
	virtual void parse_read_S_round_end() {}

	virtual void parse_read_S_square_beg() {}
	virtual void parse_read_S_square_end() {}

public:
	Parser(const string&);
	bool parse();
	void str(string&);

	~Parser() {}	

	string get_err_msg() const {return err_msg;}
	int    get_err_pos() const {return err_pos;}
};