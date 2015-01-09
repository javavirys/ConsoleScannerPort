#ifndef UTILS_H
#define UTILS_H

#include <QString>

bool isDigit    (const QString & str);

bool isIPAddress(const QString & ip);

QString *DeleteStartChar(QString * text,QChar removechar);

#endif // UTILS_H
