#pragma once

#include "TokenTypes.h"
#include "Location.h"

#include <string>
#include <any>

struct Token
{
	TokenType Type = TokenType::None;
	std::any Value;
	Location Position;

	Token(TokenType type = TokenType::None)
	{
	}

	Token(TokenType type, int32_t value, const Location& location)
		: Type(type), Value(value), Position(location)
	{
	}

	Token(TokenType type, const std::string& value, const Location& location)
		: Type(type), Value(value), Position(location)
	{
	}

	operator bool() const
	{
		return Type != TokenType::None;
	}
};
