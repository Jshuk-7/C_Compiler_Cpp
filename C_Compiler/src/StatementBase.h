#pragma once

#include "StatementTypes.h"

#include <type_traits>

class StatementBase
{
public:
	virtual StatementType GetType() const = 0;

	template <typename T>
	T* As()
	{
		if constexpr (std::is_base_of_v<StatementBase, T>())
			return (T*)this;

		return nullptr;
	}
};
