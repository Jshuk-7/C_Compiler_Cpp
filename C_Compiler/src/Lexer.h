#pragma once

#include "Func.h"
#include "Token.h"
#include "Location.h"

#include <string>

class Lexer
{
public:
	Lexer(const std::string& filepath, const std::string& source);

	Token NextToken();

	Location GetCursorLocation() const;
	Func* ParseFunction();

private:
	bool ExpectToken(TokenType type);

	char Current() const;
	bool CursorEquals(char c) const;
	bool CursorActive() const;
	bool CursorAtEnd() const;
	void TrimLeft();
	void DropLine();
	void Advance();

private:
	std::string m_Filename = "";
	std::string m_Source = "";

	uint32_t m_Cursor = 0;
	uint32_t m_LineStart = 0;
	uint32_t m_LineCount = 0;
};
