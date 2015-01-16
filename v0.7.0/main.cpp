#include <QCoreApplication>
#include <QStringList>

#include "app.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList arglist=a.arguments();

    App app(arglist);

    app.StartApp();

    app.DestroyApp();

    return 0;
}

