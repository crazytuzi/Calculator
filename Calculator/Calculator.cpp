// Calculator.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Token.h"
#include "std_lib_facilities.h"
#include "Token_stream.h"

Token_stream ts;

double expression(); // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(': case ')': // 处理 '(' expression ')'
		{
			double d = expression();
			t = ts.get();
			if (t.kind != ')') error("')' expected");
			return d;
		}
	case '8': // 使用'8'表示一个数
		return t.value; // 返回该数的值
	default:
		error("primary expected");
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
	double left = primary();
	Token t = ts.get(); // 从单词流中获取下一个单词

	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
			{
				double d = primary();
				if (d == 0) error("divide by zero");
				left /= d;
				t = ts.get();
				break;
			}
		default:
			ts.putback(t); // 将t放回到单词流中
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
	double left = term(); // 读入并计算一个项
	Token t = ts.get(); // 从单词流中获取下一个单词

	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term(); // 计算一项的值并相加
			t = ts.get();
			break;
		case '-':
			left -= term(); // 计算一项的值并相减
			t = ts.get();
			break;
		default:
			ts.putback(t); // 将t放回到单词流中
			return left; // 最终:没有更多+或-;放回结果
		}
	}
}

int main()
{
	try
	{
		double val = 0;
		while (cin)
		{
			Token t = ts.get();
			if (t.kind == 'q') break;
			if (t.kind == ';') cout << "=" << val << '\n';
			if (t.kind == '=') cout << val << '\n';
			else ts.putback(t);
			val = expression();
		}
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}
	catch (...)
	{
		cerr << "exception \n";
		return 2;
	}
	return 0;
}
