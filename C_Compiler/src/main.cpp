#include "Lexer.h"

#include <iostream>
#include <fstream>
#include <filesystem>

static constexpr auto filepath = "hello.c";

#define EXIT_DEFERED(code, ...) { printf(__VA_ARGS__); std::cin.get(); return (code); }
#define TYPE_TO_STRING(type) #type

int main()
{
	if (!std::filesystem::exists(filepath))
	{
		EXIT_DEFERED(-1, "File doesn't exist: '%s'", filepath);
	}

	std::ifstream stream(filepath);
	if (!stream.is_open())
	{
		EXIT_DEFERED(-1, "Failed to open file: '%s'", filepath);
	}

	stream.seekg(0, std::ios::end);
	size_t size = stream.tellg();
	if (size <= 0)
	{
		EXIT_DEFERED(-1, "File was empty!");
	}

	std::string source;
	source.resize(size);
	stream.seekg(0, std::ios::beg);
	stream.read(source.data(), size);

	Lexer lexer = Lexer(filepath, source);
	Func* func = lexer.ParseFunction();

	delete func;

	EXIT_DEFERED(0, "Program exited successfully...");
}
