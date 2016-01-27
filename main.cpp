#include "chatmainwindow.h"
#include <QApplication>

#include <encryption.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatMainWindow w;
    w.show();

    ChatMainWindow w2;
    w2.show();

    return a.exec();
}
