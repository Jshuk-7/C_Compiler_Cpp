#pragma once

enum class TokenType
{
	None = 0,
	Name,
	OpenParen,
	CloseParen,
	OpenCurly,
	CloseCurly,
	Semicolon,
	Number,
	String,
	Keyword,
};

inline static const char* TokenTypeToString(TokenType type)
{
	switch (type)
	{
		case TokenType::Name:		return "Name";
		case TokenType::OpenParen:	return "OpenParen";
		case TokenType::CloseParen: return "CloseParen";
		case TokenType::OpenCurly:	return "OpenCurly";
		case TokenType::CloseCurly:	return "CloseCurly";
		case TokenType::Semicolon:	return "Semicolon";
		case TokenType::Number:		return "Number";
		case TokenType::String:		return "String";
		case TokenType::Keyword:	return "Keyword";
	}

	return "None";
}
