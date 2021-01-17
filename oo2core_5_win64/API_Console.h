#pragma once

#include <vector>
#include <string>

namespace moddingApi
{
	class API_Console
	{
	public:
		static void InitializeConsole();
		static void DoConsoleCommand(std::string cmd);
	};
}