#include "peermanager.h"

PeerManager::PeerManager(QObject *parent)
    : QObject(parent)
    , broadcaster(new Broadcaster(this))
{
    connect(broadcaster, SIGNAL(broadcastReceived(quint64))
            , SLOT(broadcasterBroadcastReceived(quint64)));
}

void PeerManager::start(QNetworkAddressEntry entry, quint16 broadcastPrt
                        , int msec)
{
    broadcaster->start(entry, broadcastPrt, rand(), msec);
}

void PeerManager::stop()
{
    broadcaster->stop();
}

void PeerManager::broadcasterBroadcastReceived(quint64 peerId)
{
    if(!peerMap.contains(peerId))
    {
        peerMap.insert(peerId, NULL);
        qDebug() << this << "new peer" << peerId;
    }
}

