#include "peermanager.h"

PeerManager::PeerManager(QObject *parent)
    : QObject(parent)
    , broadcaster(new Broadcaster(this))
    , server(new QTcpServer(this))
{
    connect(broadcaster, SIGNAL(broadcastReceived(quint64,QString))
            , SLOT(broadcasterBroadcastReceived(quint64,QString)));
}

PeerManager::~PeerManager()
{
    //TODO: clear peerMap
}

void PeerManager::setUsername(const QString &username)
{
    broadcaster->setUsername(username);
}

void PeerManager::start(QNetworkAddressEntry entry, quint16 broadcastPrt
                        , int msec)
{
    if(server->listen(entry.ip()))
    {
        int port = server->serverPort();
        quint64 currentId = broadcaster->start(entry, broadcastPrt, port, msec);
        if(!currentId)
        {
            server->close();
            return;
        }

    }
}

void PeerManager::stop()
{
    broadcaster->stop();
    server->close();
}

void PeerManager::broadcasterBroadcastReceived(quint64 peerId, QString username)
{
    if(!peerMap.contains(peerId))
    {
        QTimer* timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), SLOT(peerTimeout()));
        peerMap.insert(peerId, timer);
        timer->start(5000);
        emit newPeer(peerId, username);
    }
    else
    {
        peerMap.value(peerId)->start(5000);
    }
}

void PeerManager::peerTimeout()
{
    qDebug() << "peerTimeout";
}
