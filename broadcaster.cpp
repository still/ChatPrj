#include "broadcaster.h"

Broadcaster::Broadcaster(QObject *parent)
    : QObject(parent)
    , socket(new QUdpSocket(this))
    , timer(new QTimer(this))
{
    //соединяем объекты
    connect(timer, SIGNAL(timeout()), SLOT(timerTimeout()));
    connect(socket, SIGNAL(readyRead()), SLOT(socketReadyRead()));
}

quint64 Broadcaster::start(QNetworkAddressEntry entry, quint16 broadcastPrt, quint16 serverPrt, int msec)
{
    broadcastPort = broadcastPrt;
    currentEntry = entry;

    //получаем значение идентификатора
    currentId = (((quint64)entry.ip().toIPv4Address()) << 16)
            + serverPrt;

    bool socketIsBinded = socket->bind(QHostAddress::AnyIPv4, broadcastPrt
                                       , QUdpSocket::ShareAddress
                                       | QUdpSocket::ReuseAddressHint);
    if(socketIsBinded)
    {
        timer->start(msec);
        return currentId;
    }
    return 0;
}

void Broadcaster::stop()
{
    timer->stop();
    socket->close();
}

void Broadcaster::timerTimeout()
{
    //формируем широковещательный пакет
    QByteArray datagram;
    QDataStream dataStream(&datagram, QIODevice::WriteOnly);
    dataStream << currentId;

    socket->writeDatagram(datagram, currentEntry.broadcast()
                          , broadcastPort);
}

void Broadcaster::socketReadyRead()
{
    while(socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        //размер датаграммы отличается от ожидаемого
        if(datagram.size() != sizeof(quint64))
            continue;
        //неудачное прочтение датаграммы
        if(socket->readDatagram(datagram.data(), datagram.size()) == -1)
            continue;

        //получаем идентификатор из пакета
        QDataStream dataStream(&datagram, QIODevice::ReadOnly);
        quint64 peerId;
        dataStream >> peerId;

        if(currentId != peerId)
            emit broadcastReceived(peerId);
    }
}

