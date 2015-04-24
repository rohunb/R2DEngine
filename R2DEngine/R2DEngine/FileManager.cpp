#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <assert.h>
#include "RDebug.h"

using namespace rb;

string rb::FileManager::ReadFile(const string& path)
{
	using namespace std;
	string fileContents;
	try
	{
		Debug::Log("Reading file at " + path);
		ifstream file(path);
		assert(!file.fail() && "File not found");
		stringstream stream;
		stream << file.rdbuf();
		fileContents = stream.str();
	}
	catch (std::exception e)
	{
		Debug::Error("Error reading file at path: " + path);
	}
	return fileContents;
}
