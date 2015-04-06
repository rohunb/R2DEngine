#include "RDebug.h"
#include <iostream>

void rb::Debug::Log(const string& message)
{
	DisplayMessage(message);
}

void rb::Debug::Log(const string& message, const string& file, int line)
{
	DisplayMessage(message, file, line);
}
void rb::Debug::Error(const string& message)
{
	DisplayMessage("ERROR: " + message);
}

void rb::Debug::Error(const string& message, const string& file, int line)
{
	DisplayMessage("ERROR: " + message, file, line);
}
void rb::Debug::Warning(const string& message)
{
	DisplayMessage("Warning: " + message);
}

void rb::Debug::Warning(const string& message, const string& file, int line)
{
	DisplayMessage("Warning: " + message, file, line);
}

void rb::Debug::DisplayMessage(const string& message)
{
	std::cout << message << std::endl;
}

void rb::Debug::DisplayMessage(const string& message, const string& file, int line)
{
	std::cout << message << " | File: " << file << " Line: " << line << std::endl;
}
