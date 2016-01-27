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
    connect(manager, SIGNAL(messageGetted(quint64,QString))
            , SLOT(getPeerMessage(quint64,QString)));

    //для начальной настройки чата
    enableMessaging(false);
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
    if(ui->peerList->currentRow() >= 0)
    {
        QString message = ui->messageEdit->text();
        if(message.trimmed().isEmpty())
            return;
        ui->messageEdit->clear();
        quint64 peerId = ui->peerList->currentItem()->data(Qt::UserRole)
                .toULongLong();
        appendMessage("You: " + message, peerId);
        manager->sendMessage(encodeXOR(message, profile.key), peerId);
    }
}

void ChatMainWindow::peerListRowChanged(int index)
{
    //отображение сообщений выбранного собеседника
    enableMessaging(index >= -1);
    if(index == -1)
        ui->messageListView->setModel(NULL);
    quint64 peerId = ui->peerList->item(index)->data(Qt::UserRole)
            .toULongLong();
    if(peerMessages.contains(peerId))
        ui->messageListView->setModel(peerMessages.value(peerId));
}

void ChatMainWindow::addPeer(quint64 peerId)
{
    QListWidgetItem* item = new QListWidgetItem(QString::number(peerId)
                                                , ui->peerList);
    item->setData(Qt::UserRole, QVariant(peerId));
    ui->peerList->addItem(item);
    peerMessages.insert(peerId, new QStringListModel(this));
    manager->sendUsername(profile.username, peerId);
}

void ChatMainWindow::deletePeer(quint64 peerId)
{
    int index = indexByPeerId(peerId);
    if(index >= 0)
        delete ui->peerList->item(index);
    if(peerMessages.contains(peerId))
        delete peerMessages.take(peerId);
}

void ChatMainWindow::changePeerUsername(quint64 peerId, QString username)
{
    int index = indexByPeerId(peerId);
    if(index >= 0)
        ui->peerList->item(index)->setText(username);
}

void ChatMainWindow::getPeerMessage(quint64 peerId, QString message)
{
    appendMessage(usenameByPeerId(peerId) + ": " + decodeXOR(message, profile.key)
                  , peerId);
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

QString ChatMainWindow::usenameByPeerId(quint64 peerId)
{
    int index = indexByPeerId(peerId);
    if(index >= 0)
        return ui->peerList->item(index)->text();
    return QString();
}

void ChatMainWindow::enableMessaging(bool ison)
{
    ui->messageButton->setEnabled(ison);
    ui->messageEdit->setEnabled(ison);
    ui->messageListView->setEnabled(ison);
}

void ChatMainWindow::appendMessage(QString message, quint64 peerId)
{
    if(peerMessages.contains(peerId))
    {
        QStringListModel* model = peerMessages.value(peerId);
        model->insertRow(model->rowCount());
        model->setData(model->index(model->rowCount() - 1), message);
    }
}
