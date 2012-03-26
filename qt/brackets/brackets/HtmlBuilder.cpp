#include "StdAfx.h"
#include "HtmlBuilder.h"
#include <iostream>

using namespace std;

namespace {
	const string TABLE = "<table width = 100% border = 1 cellpadding = 7 cellspacing = 0>";
	const string TH1   = "<th align = center bgcolor = #97da97 colspan = 1>";
	const string TH3   = "<th align = center bgcolor = #97da97 colspan = 3>";
	const string TD    = "<td>";
	const string TD3   = "<td colspan = 3>";
}

HtmlBuilder::HtmlBuilder(const string& istr) : Parser(istr)
{
	html.clear();
	valid = parse();
}

void HtmlBuilder::parse_beg() 
{
	html +=	"<table width = 100%><tr>";
}

void HtmlBuilder::parse_end() 
{
	html += "</tr></table>";
}

void HtmlBuilder::parse_read_ch() 
{
	html += TD;
	html += ch;
	html += "</td>";
}

void HtmlBuilder::parse_empty_char()
{
	html += TD3;
	html += 'E';
	html += "</td>";
}

void HtmlBuilder::parse_read_S_beg()
{
	html +=	TD +  TABLE +  "<tr>";
/* Не совсем так, как нужно */
	if (ch == '$')
		html +=	TH1 + "S</th>";
	else
		html +=	TH3 + "S</th>";	

	html += "</tr><tr>"; 
}

void HtmlBuilder::parse_read_S_end() 
{
	html +=	"</tr></table></td>";
}


void HtmlBuilder::parse_read_S_round_beg() 
{
	html += TD + TABLE + "<tr>";

	if (ch == ')')
		html +=	TH1 + "S_ROUND</th>";
	else
		html += TH3 + "S_ROUND</th>";	

	html += "</tr><tr>";
}

void HtmlBuilder::parse_read_S_round_end() 
{
	html +="</tr></table></td>";
}

void HtmlBuilder::parse_read_S_square_beg() 
{
	html += TD + TABLE + "<tr>";

	if (ch == ']')
		html +=	TH1 + "S_SQUARE</th>";
	else
		html += TH3 + "S_SQUARE</th>";

	html += "</tr><tr>";
}

void HtmlBuilder::parse_read_S_square_end() 
{
	html += "</tr></table></td>";
}

string HtmlBuilder::getHtml() const
{
	return html;
}