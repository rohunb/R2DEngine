#include "RDebug.h"
#include <iostream>
#include "GL_Includes.h"

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

void rb::Debug::CheckGLError(const string& file, int line)
{
	const GLenum glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		printf("GLERROR %s | file %s at line %d", gluErrorString(glError), file.c_str(), line);
		assert(false);
	}
}

void rb::Debug::DisplayMessage(const string& message)
{
	std::cout << message << std::endl;
}

void rb::Debug::DisplayMessage(const string& message, const string& file, int line)
{
	std::cout << message << " | File: " << file << " Line: " << line << std::endl;
}
