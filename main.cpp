#include "chatmainwindow.h"
#include <QApplication>

#include <encryption.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatMainWindow w;
    w.show();

    return a.exec();
}
