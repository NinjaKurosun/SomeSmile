#include <fstream>
#include <Windows.h>
#include <codecvt>
#include <map>

#include "Switcher.h"
using namespace std;

#define DllExport extern "C" __declspec(dllexport)

Switcher Swit;

BOOL APIENTRY DllMain(HANDLE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved)
{
	HKEY key;

	if (RegCreateKeyEx(HKEY_CURRENT_USER,
		L"SOFTWARE\\MySchizophrenia\\SomeSmile\\Switcher",
		0,
		NULL,
		REG_OPTION_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&key,
		NULL) == ERROR_SUCCESS)
	{

		DWORD Size = MAX_PATH;
		BYTE* PathToTrFile = new BYTE[Size];

		if (RegQueryValueExA(key,
			"TrFile",
			NULL,
			NULL,
			PathToTrFile,
			&Size) == ERROR_SUCCESS)
		{
			wifstream TrFile((char*)PathToTrFile);
			TrFile.imbue(std::locale(TrFile.getloc(), new std::codecvt_utf16<wchar_t, 1114111UL, std::little_endian>));

			map<wstring, wstring> KeysAndValues;

			wstring Key;
			wstring Value;
			while (TrFile)
			{
				TrFile >> Key;
				TrFile >> Value;

				KeysAndValues[Key] = Value;
			}
			Swit.SetKeysAndValues(KeysAndValues);
		}

		delete[] PathToTrFile;
		PathToTrFile = NULL;

		//MessageBox(0, L"Here", L"Error", 0);

		BYTE AutoTr[4];
		Size = sizeof(DWORD);
		if (RegQueryValueExA(key,
			"Auto-&Translate",
			NULL,
			NULL,
			AutoTr,
			&Size) == ERROR_SUCCESS)
		{
			//MessageBoxA(0,(CHAR*)AutoTr,"",0);
				Swit.SetFlags(AutoTr[0]);
		}
	}
	return TRUE;
}




DllExport LRESULT CALLBACK KeyboardProc(int nCode,
	WPARAM wParam, LPARAM lParam)
{

	if (nCode >= 0 && (HIWORD(lParam) & KF_UP))
	{
		switch (wParam)
		{
		case VK_BACK:
			--Swit;
			break;
		case VK_CONTROL:
			Swit.Translate();
			break;

		default:
			Swit.PushBack(wParam, lParam);
			break;
		}
		//MessageBox(0, L"yes1", L"yes1", 0);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}