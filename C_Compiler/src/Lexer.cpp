#include "Lexer.h"

#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <stdlib.h>

static std::unordered_map<char, TokenType> s_PuncuationTokens =
{
	{ '(', TokenType::OpenParen  },
	{ ')', TokenType::CloseParen },
	{ '{', TokenType::OpenCurly  },
	{ '}', TokenType::OpenCurly  },
	{ ';', TokenType::Semicolon  },
};

Lexer::Lexer(const std::string& filepath, const std::string& source)
	: m_Source(source)
{
	m_Filename = std::filesystem::path(filepath).filename().string();
}

Func* Lexer::ParseFunction()
{
	Func* func = new Func();

	const bool result = ExpectToken(TokenType::Name);
	if (result)
		return func;

	return nullptr;
}

bool Lexer::ExpectToken(TokenType type)
{
	Token token = NextToken();
	if (!token)
	{
		std::cerr << GetCursorLocation() << " Error: expected " << TokenTypeToString(type) << " found eof" << '\n';
		return false;
	}

	if (token.Type != type)
	{
		std::cerr << GetCursorLocation() << " Error: expected " << TokenTypeToString(type) << " found " << TokenTypeToString(token.Type) << '\n';
		return false;
	}

	return true;
}

char Lexer::Current() const
{
	return m_Source[m_Cursor];
}

bool Lexer::CursorEquals(char c) const
{
	return m_Source[m_Cursor] == c;
}

Location Lexer::GetCursorLocation() const
{
	return Location{ m_Filename, m_LineCount, m_Cursor - m_LineStart };
}

bool Lexer::CursorActive() const
{
	return m_Cursor < m_Source.size();
}

bool Lexer::CursorAtEnd() const
{
	return !CursorActive();
}

void Lexer::TrimLeft()
{
	while (CursorActive() && isspace(Current()))
		Advance();
}

void Lexer::DropLine()
{
	while (CursorActive() && !CursorEquals('\n'))
		Advance();

	// remove the new line character
	if (CursorActive())
		Advance();
}

void Lexer::Advance()
{
	if (CursorAtEnd())
		return;

	m_Cursor++;

	if (CursorEquals('\n'))
	{
		m_LineStart = m_Cursor;
		m_LineCount++;
	}
}

Token Lexer::NextToken()
{
	TrimLeft();

	while (CursorActive() && CursorEquals('#'))
	{
		DropLine();
		TrimLeft();
	}

	if (CursorAtEnd())
		return {};

	Location location = GetCursorLocation();
	char first = Current();

	if (isalpha(first))
	{
		uint32_t start = m_Cursor;
		
		while (CursorActive() && isalnum(Current()))
			Advance();

		std::string value = m_Source.substr(start, m_Cursor - start);
		return Token(TokenType::Name, value, location);
	}

	if (s_PuncuationTokens.contains(first))
	{
		Advance();
		return Token(s_PuncuationTokens.at(first), std::string(&first, 1), location);
	}

	if (first == '"')
	{
		Advance();
		uint32_t start = m_Cursor;

		while (CursorActive() && !CursorEquals('"'))
			Advance();

		if (CursorActive())
		{
			std::string value = m_Source.substr(start, m_Cursor - start);
			Advance();
			return Token(TokenType::String, value, location);
		}
		
		std::cerr << GetCursorLocation() << " Error: unterminated string literal" << '\n';
	}

	if (isdigit(first))
	{
		uint32_t start = m_Cursor;

		while (CursorActive() && isdigit(Current()))
			Advance();

		int32_t value = std::atoi(m_Source.substr(start, m_Cursor - start).c_str());
		return Token(TokenType::Number, value, location);
	}

	return {};
}
