#include "tcpconnection.h"

TcpConnection::TcpConnection(QObject *parent) : QTcpSocket(parent)
{
    connect(this, SIGNAL(connected()), SLOT(handshake()));
    connect(this, SIGNAL(readyRead()), SLOT(readyReadHandler()));
    isHandhaked = false;
}

TcpConnection::~TcpConnection()
{
}

void TcpConnection::setCurrentId(quint64 id)
{
    currentId = id;
}

quint64 TcpConnection::getCurrentId()
{
    return currentId;
}

void TcpConnection::handshake()
{
    if(isHandhaked)
        return;
    QByteArray data;
    QDataStream dataStream(&data, QIODevice::WriteOnly);
    dataStream << currentId;
    write(data);
    isHandhaked = true;
}

void TcpConnection::readyReadHandler()
{
    if(bytesAvailable() >= (qint64)sizeof(quint64))
    {
        QByteArray data = read(sizeof(quint64));
        QDataStream dataStream(&data, QIODevice::ReadOnly);
        quint64 peerId;
        dataStream >> peerId;
        if(!isHandhaked)
            handshake();
        setCurrentId(peerId);
        emit ready(peerId);
    }
}
