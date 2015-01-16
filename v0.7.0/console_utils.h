/*
 ******************************Заголовочный файл************************************
 ************Здесь нвходятся прототипы функций для работы с консолью****************
*/
#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <QString>
#include <QTextStream>

enum ConsoleColor
{
                Black         = 0,
                Blue          = 1,
                Green         = 2,
                Cyan          = 3,
                Red           = 4,
                Magenta       = 5,
                Brown         = 6,
                LightGray     = 7,
                DarkGray      = 8,
                LightBlue     = 9,
                LightGreen    = 10,
                LightCyan     = 11,
                LightRed      = 12,
                LightMagenta  = 13,
                Yellow        = 14,
                White         = 15
};

void qCout(const QString &text, ConsoleColor color);

#endif // CONSOLE_UTILS_H
