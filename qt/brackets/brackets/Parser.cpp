#include "StdAfx.h"
#include "Parser.h"

using std::string;

Parser::Parser(const string& istr) : chSeq(istr) { }

void Parser::str(string& s)
{
	chSeq.str(s);
	err_msg.clear();
	err_pos = 0;
}

bool Parser::parse()
{
	valid = true;
	if (chSeq.ch() == '[' || chSeq.ch() == '(' || chSeq.ch() == '$')
	{
		parse_beg();		
			//parse_read_ch();
			ch = chSeq.ch();

			read_S();
		parse_end();

		if (!chSeq.eof())
			error("лишние символы");
	}
	else
		error("ожидается ( или [");

	return valid;
}

void Parser::error(const string& s)
{
	if (valid)
	{
		err_msg = s;
		err_pos = chSeq.get_count();
		valid   = false;
	}
}

void Parser::read_S()
{
	parse_read_S_beg();

	if (ch == '(')
	{
		if (ch == '(')
			read_ch(); 
		else 
			error("ожидается (");
		read_S_round();
		read_S();
	}
	else if (ch == '[')	
	{
		if (ch == '[')
			read_ch();
		else 
			error("ожидается [");
		read_S_square();
		read_S();
	}
	else
	parse_empty_char();

	parse_read_S_end();
}

void Parser::read_S_round()
{
	parse_read_S_round_beg();

	if (ch == '[')
	{
		if (ch == '[')
			read_ch();
		else
			error("ожидается [");
		read_S_square();		
		read_S_round();		
	} 
	else if (ch == ')')
	{
		if (ch == ')')
			read_ch();
		else 
			error("ожидается )");
	}
	else error("ожидается [ или )");				

	parse_read_S_round_end();
}

void Parser::read_S_square()
{	
	parse_read_S_square_beg();

	if (ch == '(')
	{
		if (ch == '(')
			read_ch();
		else
			error("ожидается (");			
		read_S_round();		
		read_S_square();	
	} 
	else if (ch== ']')
	{
		if (ch == ']')
			read_ch();
		else 
			error("ожидается ]");
	}
	else error("ожидается ( или ]");	

	parse_read_S_square_end();
}

void Parser::read_ch() 
{
	parse_read_ch();

	chSeq.next();
	ch = chSeq.ch();
}