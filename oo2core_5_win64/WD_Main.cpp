#include "WD_Main.h"
#include "API_Console.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace moddingApi;

DWORD WINAPI WD_Main::Start()
{
	API_Console::InitializeConsole();

	// Console allocation
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);

	cout << "====== Walking Dead: Modding Console ======" << endl;

	while (true)
	{
		if (GetKeyState('Q') < 0)
		{
			std::string cmd = "SetTimeScale 1";
			API_Console::DoConsoleCommand(cmd);
		}
		else if (GetKeyState('E') < 0)
		{
			std::string cmd = "SetTimeScale 2";
			API_Console::DoConsoleCommand(cmd);
		}
		else if (GetKeyState('R') < 0)
		{
			std::string cmd = "GetTimeScale";
			API_Console::DoConsoleCommand(cmd);
		}
		else
		{
			//leaving this on hangs the console and any input detection
			/*
			std::string cmd;
			cout << "> ";
			cin >> cmd;

			API_Console::DoConsoleCommand(cmd);
			*/
		}
		
		Sleep(100);
	}

	return 0;
}