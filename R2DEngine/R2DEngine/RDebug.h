#ifndef R_DEBUG_H_
#define R_DEBUG_H_

#include "RString.h"

namespace rb
{
	class Debug
	{
	public:
		Debug() = delete;
		static void Log(const string& message);
		static void Log(const string& message, const string& file, int line);
		static void Error(const string& message);
		static void Error(const string& message, const string& file, int line);
		static void Warning(const string& message);
		static void Warning(const string& message, const string& file, int line);

	private:
		static void DisplayMessage(const string& message, const string& file, int line);
		static void DisplayMessage(const string& message);
	};
}
#endif // !R_DEBUG_H_
