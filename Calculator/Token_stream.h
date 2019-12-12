#pragma once

#include "Token.h"

class Token_stream
{
public:
	Token_stream();
	~Token_stream();

	Token get(); // 获取一个单词

	void putback(Token t); // 放回一个单词

private:

	bool full{false}; // 缓存区里是否有单词?

	class Token buffer; // 存储通过putback()放回的单词的缓存区
};
