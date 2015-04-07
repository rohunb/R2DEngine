#ifndef R_FILE_MANAGER_H_
#define R_FILE_MANAGER_H_

#include "RString.h"

namespace rb
{
	class FileManager
	{
	public:
		static string ReadFile(const string& path);
	};
}
#endif // R_FILE_MANAGER_H_
