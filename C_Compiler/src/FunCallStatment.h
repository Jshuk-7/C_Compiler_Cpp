#pragma once

#include "StatementBase.h"

#include <string>

class FunCallStatement : public StatementBase
{
public:
	FunCallStatement();

	static StatementType GetStaticType() { return StatementType::FunCall; }
	StatementType GetType() const override { return GetStaticType(); }

private:
	std::string m_Name = "";
	std::string m_Args = "";
};
