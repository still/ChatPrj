#include "chatmainwindow.h"
#include "ui_chatmainwindow.h"

ChatMainWindow::ChatMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatMainWindow)
    , manager(new PeerManager(this))
{
    ui->setupUi(this);
    setupUi();

    connect(manager, SIGNAL(peerToAdd(quint64)), SLOT(addPeer(quint64)));
    connect(manager, SIGNAL(peerToDelete(quint64)), SLOT(deletePeer(quint64)));
    connect(manager, SIGNAL(usernameChanged(quint64,QString))
            , SLOT(changePeerUsername(quint64,QString)));

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
            manager->start(settings.entry, 30400, 1000);
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
        Profile oldProfile = profile;
        profile = dlg.getData();
        if(oldProfile.username != profile.username)
            manager->sendUsername(profile.username);
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

void ChatMainWindow::addPeer(quint64 peerId)
{
    QListWidgetItem* item = new QListWidgetItem(QString::number(peerId)
                                                , ui->peerList);
    item->setData(Qt::UserRole, QVariant(peerId));
    ui->peerList->addItem(item);
    manager->sendUsername(profile.username, peerId);
}

void ChatMainWindow::deletePeer(quint64 peerId)
{
    int index = indexByPeerId(peerId);
    if(index >= 0)
        delete ui->peerList->item(index);
}

void ChatMainWindow::changePeerUsername(quint64 peerId, QString username)
{
    int index = indexByPeerId(peerId);
    if(index >= 0)
        ui->peerList->item(index)->setText(username);
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

int ChatMainWindow::indexByPeerId(quint64 peerId)
{
    for(int i = 0; i < ui->peerList->count(); i++)
        if(ui->peerList->item(i)->data(Qt::UserRole).toULongLong() == peerId)
            return i;
    return -1;
}
