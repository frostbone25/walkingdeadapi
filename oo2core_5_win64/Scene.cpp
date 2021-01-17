#include "Scene.h"
#include "oo2core_5_win64.h"

#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace moddingApi;

string * _fastcall Scene::GetWorldSceneName()
{
	string * name = new string();

	typedef string * (__fastcall * fc_funct)(string * result);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(oo2core_5_win64::moduleBase + 0x203A80);

	cout << * fc_cc_funct(name) << endl;

	return fc_cc_funct(name);
}