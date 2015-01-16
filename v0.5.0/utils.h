#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QStringList>

bool isDigit    (const QString & str);

bool isIPAddress(const QString & ip);

QString *DeleteStartChar(QString * text,QChar removechar);

int mod(int var1,int var2);

#endif // UTILS_H
