#include "console_utils.h"

#ifdef WIN32
#include <windows.h>

#endif

#include <iostream>

#ifdef WIN32
// устанавливает цвет текста и подложки в консоли
void SetColor(int text, int background)
{
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

// устанавливает цвет текста и подложки в консоли
void SetColor(int text, ConsoleColor/*int*/ background)
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
#endif

void qCout(const QString &text, ConsoleColor color)
{
#ifdef WIN32
    SetColor(color,Black);
    std::cout<<text.toStdString().c_str();
    SetColor(LightGray,Black);

#else
    std::cout<<text.toStdString().c_str();
#endif
}
