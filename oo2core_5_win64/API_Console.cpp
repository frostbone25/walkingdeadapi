#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "oo2core_5_win64.h"
#include "API_Console.h"
#include "Scene.h"

using namespace std;
using namespace moddingApi;

// Console Functions
vector<string> consoleCommands;
vector<uintptr_t> consoleFunctions;
vector<int> consoleParams;
void AddCommand(string, uintptr_t, int);
int GetCommandIndex(string);

// Command Functions
void c_Help();
void c_ConvertMessage();
void c_SetTimeScale();
void c_GetTimeScale();

void API_Console::InitializeConsole()
{
	AddCommand("Help", (uintptr_t)c_Help, 0);
	AddCommand("ConvertMessage", (uintptr_t)c_ConvertMessage, 1);
	AddCommand("GetWorldSceneName", (uintptr_t)Scene::GetWorldSceneName, 1);
	AddCommand("SetTimeScale", (uintptr_t)c_SetTimeScale, 0);
	AddCommand("GetTimeScale", (uintptr_t)c_GetTimeScale, 0);
}

typedef void(__stdcall * f)();
f Function;

void API_Console::DoConsoleCommand(string Input)
{
	string Command = Input;

	int ind = GetCommandIndex(Command);
	if (ind != -1)
	{
		Function = (f)consoleFunctions[ind];
		Function();

		cout << endl;
	}
	else
	{
		cout << "Command not found" << endl;
	}
}

void c_Help()
{
	cout << endl;
	cout << "Available commands:" << endl;
	for (int x = 0; x < consoleCommands.size(); x++)
	{
		cout << consoleCommands[x] << endl;
	}
}

#include "Scene.h"
void c_ConvertMessage()
{
	std::string param1;

	//cout << "MSG >> ";
	//cin >> param1;
	//char * param1_c = strcpy(new char[param1.length() + 1], param1.c_str());

	cout << "Scene: " << Scene::GetWorldSceneName() << endl;
}

void c_SetTimeScale()
{
	float t; // float variable to store the new timescale

	cout << "Timescale: "; // show Timescale: on console
	cin >> t; // get float value from keyboard
	cout << endl; // end line

	typedef void(__fastcall* fc_funct)(float scale); // declare our function to call from the exe. it takes a float as a parameter
	fc_funct fc_cc_funct = (fc_funct)(oo2core_5_win64::moduleBase + 0x348F70); // offset 0x348F70 in GameApp.exe is where the function is
	fc_cc_funct(t); // call the function with our parameter

	cout << "Set timescale to " << t << endl; // show on console
}

void c_GetTimeScale()
{
	typedef float(__fastcall* fc_funct)(); // declare our function to call from the exe. no parameters
	fc_funct fc_cc_funct = (fc_funct)(oo2core_5_win64::moduleBase + 0x348F60); // offset 0x348F60 in GameApp.exe is where the function is
	float f = fc_cc_funct(); // declare float to store the returned value, and then call function
	cout << "Actual timescale: " << f << endl; // show value on console
}

void AddCommand(string command, uintptr_t function, int paramCount)
{
	consoleCommands.push_back(command);
	consoleFunctions.push_back(function);
	consoleParams.push_back(paramCount);
}

int GetCommandIndex(string command)
{
	int cmd = -1;

	for (int x = 0; x < consoleCommands.size(); x++)
	{
		if (command == consoleCommands[x])
		{
			cmd = x;
			x = consoleCommands.size();
		}
	}

	return cmd;
}