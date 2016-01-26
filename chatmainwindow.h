#ifndef CHATMAINWINDOW_H
#define CHATMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChatMainWindow;
}

class ChatMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatMainWindow(QWidget *parent = 0);
    ~ChatMainWindow();

private:
    Ui::ChatMainWindow *ui;
};

#endif // CHATMAINWINDOW_H
