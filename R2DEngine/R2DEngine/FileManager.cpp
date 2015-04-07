#include "FileManager.h"
#include <fstream>
#include <sstream>
#include "RDebug.h"

using namespace rb;

string rb::FileManager::ReadFile(const string& path)
{
	using namespace std;
	ifstream file(path, ios::binary);
	if (file.fail())
	{
		Debug::Error("Error reading file at path: " + path);
		return "";
	}
	stringstream stream;
	stream << file.rdbuf();
	return stream.str();
}
