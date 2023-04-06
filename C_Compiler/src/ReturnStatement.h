#pragma once

#include "StatementBase.h"

#include <string>

class ReturnStatement : public StatementBase
{
public:
	ReturnStatement();

	static StatementType GetStaticType() { return StatementType::Return; }
	StatementType GetType() const override { return GetStaticType(); }

private:
	std::string m_Expression = "";
};
