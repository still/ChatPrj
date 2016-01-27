#include "peermanager.h"

PeerManager::PeerManager(QObject *parent)
    : QObject(parent)
    , broadcaster(new Broadcaster(this))
    , server(new TcpServer(this))
{
    connect(broadcaster, SIGNAL(broadcastReceived(quint64))
            , SLOT(broadcasterBroadcastReceived(quint64)));

    connect(this, SIGNAL(broadcastPeerConnection(TcpConnection*))
            , SLOT(peerConnection(TcpConnection*)));

    connect(server, SIGNAL(peerConnection(TcpConnection*))
            , SLOT(peerConnection(TcpConnection*)));
}

void PeerManager::start(QNetworkAddressEntry entry, quint16 broadcastPrt
                        , int msec)
{
    server->listen(entry.ip());
    broadcaster->start(entry, broadcastPrt, server->serverPort(), msec);
}

void PeerManager::stop()
{
    server->close();
    broadcaster->stop();
}

void PeerManager::broadcasterBroadcastReceived(quint64 peerId)
{
    if(!peerMap.contains(peerId))
    {
        QHostAddress address;
        address.setAddress(peerId >> 16);
        quint16 port = peerId;
        TcpConnection* connection = new TcpConnection(this);
        emit broadcastPeerConnection(connection);
        connection->connectToHost(address, port);
    }
}

void PeerManager::peerConnection(TcpConnection *connection)
{
    connection->setCurrentId(broadcaster->getCurrentId());
    connect(connection, SIGNAL(ready(quint64))
            , SLOT(connectionReady(quint64)));
    connect(connection, SIGNAL(disconnected())
            , SLOT(connectionDisconnected()));
}

void PeerManager::connectionReady(quint64 peerId)
{
    TcpConnection* connection = qobject_cast<TcpConnection*>(sender());
    if(peerMap.contains(peerId))
    {
        connection->close();
    }
    else
    {
        peerMap.insert(peerId, connection);
        emit peerToAdd(peerId);
    }
}

void PeerManager::connectionDisconnected()
{
    TcpConnection* connection = qobject_cast<TcpConnection*>(sender());
    if(peerMap.contains(connection->getCurrentId()))
    {
        peerMap.remove(connection->getCurrentId());
        emit peerToDelete(connection->getCurrentId());
    }
    connection->deleteLater();
}
