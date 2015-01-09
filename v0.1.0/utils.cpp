#include "utils.h"

#include <QStringList>


bool isDigit    (const QString & str)
{
    int len=str.size();
    for(int i=0;i<len;i++)
    {
        if(str[i].isDigit())
            continue;
        else return false;
    }

    return true;
}

bool isIPAddress(const QString & ip)
{
    QStringList list =ip.split('.');
    if(list.size()!=4)
    {
        return false;
    }
    for(int i=0;i<list.size();i++)
    {
        if(!isDigit(list[i]))
            return false;
    }

    return true;
}

QString *DeleteStartChar(QString * text,QChar removechar)
{
    int count=0;
    int len=text->size();
    for(int i=0;i<len;i++)
    {
        if((*text)[i]==removechar)
        {
            count++;
        }else {
            if(count>0)
                text->remove(0,count);
            break;
        }
    }
    return text;
}
