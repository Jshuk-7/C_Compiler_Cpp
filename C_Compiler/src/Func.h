#pragma once

#include "StatementBase.h"

#include <vector>
#include <string>

class Func
{
public:
	Func();

private:
	std::string m_Name = "";
	std::vector<StatementBase*> m_Body;
};
