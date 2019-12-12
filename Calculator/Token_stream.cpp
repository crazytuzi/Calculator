#include "stdafx.h"
#include "Token_stream.h"
#include "std_lib_facilities.h"


Token_stream::Token_stream()
{
}


Token_stream::~Token_stream()
{
}

Token Token_stream::get()
{
	if (full) // 缓存区里是否已经有一个单词?
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch; //注意 >> 运算符会跳过空白(空格,新行,制表符等)

	switch (ch)
	{
	case ';':
	case '=':
	case 'q':
	case '(': case '+': case '-': case '*': case '/': case ')':
		return Token(ch);
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		{
			cin.putback(ch); // 将数字(或小数点)放回到标准输入流中
			double val;
			cin >> val; // 读入一个浮点数
			return Token('8', val); // 用'8'表示"这是一个数"
		}
	default:
		error("Bad token");
	}
}

void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");

	buffer = t; // 拷贝t到缓存区

	full = true; // 现在缓存区被占用
}
