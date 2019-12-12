#pragma once
class Token
{
public:
	Token();
	~Token();

	Token(char ch);

	Token(char ch, double v);

	char kind; // 单词类型

	double value; // 对数值类型的单词:记录它的值
};
