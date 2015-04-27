#ifndef R_DEBUG_H_
#define R_DEBUG_H_

#include "RString.h"

namespace rb
{
	namespace Debug
	{
#define CheckOpenGLError() CheckGLError(__FILE__, __LINE__)

		void Log(const string& message);
		void Log(const string& message, const string& file, int line);
		void Error(const string& message);
		void Error(const string& message, const string& file, int line);
		void Warning(const string& message);
		void Warning(const string& message, const string& file, int line);
		void CheckGLError(const string& file, int line);

		void DisplayMessage(const string& message, const string& file, int line);
		void DisplayMessage(const string& message);
	}
}
#endif // !R_DEBUG_H_
