#include "Switcher.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
Switcher::Switcher(const char& flags)
{
    NumberOfSpace = 0;
    Flags = flags;
}
Switcher::Switcher() : Switcher(0)
{
}
Switcher::Switcher(const std::map<std::wstring, std::wstring>& aKeysAndValue, const char& aFlags) : Switcher(aFlags)
{
    KeysAndValue = aKeysAndValue;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
char Switcher::SetFlags(SwitcherFlags flags)
{
    Flags |= flags;
    return Flags;
}

char Switcher::SetFlags(const char &flags)
{
    Flags |= flags;
    return Flags;
}

void Switcher::Translate()
{
    HWND TextWin = GetFocus();

    if (KeysAndValue.count(KeyWord))
    {
        std::wstring wstr = KeysAndValue[KeyWord];
        for (int i = 0; i < wcslen(KeyWord.c_str()) + NumberOfSpace; i++)//Clear Keyword
        {
            SendMessage(TextWin, WM_KEYDOWN, VK_BACK, 1);
            SendMessage(TextWin, WM_KEYUP, VK_BACK, 1);
        }
        for (int i = 0; i < wcslen(wstr.c_str()); i++)//Send Word-Value
        {
            SendMessage(TextWin, WM_CHAR, wstr[i], 1);
        }
        SendMessage(TextWin, WM_CHAR, L' ', 1);

        //MessageBox(0,L"Here",L"Error",0);
    }
    KeyWord.clear();
}

void Switcher::PushBack(WPARAM wParam, LPARAM lParam)
{
    if (wParam != VK_SPACE &&
        wParam != VK_RETURN &&
        wParam != VK_MENU &&
        wParam != VK_SHIFT)
    {
        if (NumberOfSpace)
        {
            NumberOfSpace = 0;
            KeyWord.clear();
        }
        BYTE KeyboardState[256];
        if (GetKeyboardState(KeyboardState))
        {
            WCHAR KeyOfWchar;
            ToUnicode(wParam, LOBYTE(HIWORD(lParam)), KeyboardState, &KeyOfWchar, 1, 0);

            KeyWord.push_back(KeyOfWchar);
            //MessageBox(0, &KeyOfWchar, KeyWord.c_str(), 0);
            NumberOfSpace = 0;
            return;
        }
    }
    else if (wParam == VK_SPACE) NumberOfSpace++;
    if (Flags & AutoTranslate) Translate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Switcher& Switcher::operator--()
{
    if (NumberOfSpace) NumberOfSpace--;
    else
    {
        if (!KeyWord.empty()) KeyWord.pop_back();
    }
    return *this;
}

Switcher Switcher::operator--(int)
{
    Switcher temp(*this);

    --(*this);
    return temp;
}

void Switcher::SetKeysAndValues(const std::map<std::wstring, std::wstring>& LKeysAndEmoji)
{
    KeysAndValue = LKeysAndEmoji;
}