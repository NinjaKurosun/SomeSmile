#pragma once
#include <Windows.h>
#include <string>
#include <map>

class Switcher
{
	char Flags;
	int  NumberOfSpace;

	std::wstring KeyWord;
	std::map<std::wstring, std::wstring> KeysAndValue;
public:

	enum SwitcherFlags
	{
		AutoTranslate = 0b00000001
	};

	Switcher();
	Switcher(const char& flags);
	Switcher(const std::map<std::wstring, std::wstring>& aKeysAndValue, const char& aFlags = 0);
	void SetKeysAndValues(const std::map<std::wstring, std::wstring>& LKeysAndEmoji);

	void PushBack(WPARAM wParam, LPARAM lParam);
	char SetFlags(SwitcherFlags flags);
	char SetFlags(const char &flags);
	void Translate();

	Switcher& operator--();
	Switcher operator--(int);
};
