#include "chatmainwindow.h"
#include "ui_chatmainwindow.h"

ChatMainWindow::ChatMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatMainWindow)
    , manager(new PeerManager(this))
{
    ui->setupUi(this);
    setupUi();

    connect(manager, SIGNAL(newPeer(quint64,QString)), SLOT(managerNewPeer(quint64,QString)));

    //для начальной настройки чата
    show();
    settingsAction->trigger();
    profileAction->trigger();
}

ChatMainWindow::~ChatMainWindow()
{
    delete ui;
}

void ChatMainWindow::settingsActionTriggered()
{
    //отображение формы настроек, обработка формы
//    qDebug() << this << "settingsActionTriggered";
    SettingsDialog dlg;
    dlg.setData(settings);
    if(dlg.exec())
    {
        settings = dlg.getData();
        if(!settings.entry.ip().isNull()) {
            manager->stop();
            manager->start(settings.entry, 30400, 1000);
//            ui->statusBar->showMessage(QString::number(manager->currentId()));
        }
    }
}

void ChatMainWindow::profileActionTriggered()
{
    //отображение формы профиля, обработка формы
//    qDebug() << this << "profileActionTriggered";
    ProfileDialog dlg;
    dlg.setData(profile);
    if(dlg.exec())
    {
        profile = dlg.getData();
        manager->setUsername(profile.username);
    }
}

void ChatMainWindow::messageBtnClicked()
{
    //отсылка введенного сообщения
    qDebug() << this << "messageBtnClicked";
}

void ChatMainWindow::peerListRowChanged(int index)
{
    //отображение сообщений выбранного собеседника
    qDebug() << this << "peerListRowChanged" << index;
}

void ChatMainWindow::managerNewPeer(quint64 peerId, QString username)
{
    QString title = username.isEmpty() ? QString::number(peerId) : username;
    QListWidgetItem* item = new QListWidgetItem(title, ui->peerList);
    item->setData(Qt::UserRole, QVariant(peerId));
    ui->peerList->addItem(item);
}

void ChatMainWindow::setupUi()
{
    //создание QAction настроек
    settingsAction = new QAction(QIcon(":settings"), tr("Settings"), this);
    connect(settingsAction, SIGNAL(triggered(bool)), SLOT(settingsActionTriggered()));
    ui->mainToolBar->addAction(settingsAction);

    //создание QAction профиля
    profileAction = new QAction(QIcon(":profile"), tr("Profile"), this);
    connect(profileAction, SIGNAL(triggered(bool)), SLOT(profileActionTriggered()));
    ui->mainToolBar->addAction(profileAction);

    //обработка кнопки отсылки сообщения
    connect(ui->messageButton, SIGNAL(clicked(bool)), SLOT(messageBtnClicked()));

    //обработка выбора собеседника
    connect(ui->peerList, SIGNAL(currentRowChanged(int)), SLOT(peerListRowChanged(int)));
}
