#pragma once

#include <iostream>
#include <string>

struct Location
{
	std::string Filename = "";
	uint32_t Row = 0;
	uint32_t Column = 0;

	Location() = default;
	Location(const std::string& filename, uint32_t row, uint32_t column)
		: Filename(filename), Row(row), Column(column)
	{
	}

	friend std::ostream& operator<<(std::ostream& stream, const Location& location)
	{
		return stream << location.Filename << ':' << location.Row + 1 << ':' << location.Column;
	}
};
