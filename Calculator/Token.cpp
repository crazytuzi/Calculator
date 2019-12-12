#include "stdafx.h"
#include "Token.h"


Token::Token()
{
}


Token::~Token()
{
}

Token::Token(char ch)
{
	kind = ch;
}

Token::Token(char ch, double v)
{
	kind = ch;

	value = v;
}
