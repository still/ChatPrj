#include "tcpconnection.h"

TcpConnection::TcpConnection(QObject *parent) : QTcpSocket(parent)
{
    connect(this, SIGNAL(connected()), SLOT(handshake()));
    connect(this, SIGNAL(readyRead()), SLOT(readyReadHandler()));
    isHandhaked = false;
    state = WAIT;
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

void TcpConnection::sendUsername(const QString &username)
{
    quint16 packetId = 1;
    quint16 packetSize = (quint16)username.size();
    QByteArray packet;
    QDataStream packetStream(&packet, QIODevice::WriteOnly);
    packetStream << packetId << packetSize;
    packet.append(username);
    write(packet);
    qDebug() << "write" << packet;
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
    packetId = 0;
    packetSize = 0;
}

void TcpConnection::readyReadHandler()
{
    while(bytesAvailable() > 0) {
        if(state == WAIT)
        {
            if(bytesAvailable() < (qint64)sizeof(quint64))
                return;
            QByteArray data = read(sizeof(quint64));
            QDataStream dataStream(&data, QIODevice::ReadOnly);
            quint64 peerId;
            dataStream >> peerId;
            if(!isHandhaked)
                handshake();
            setCurrentId(peerId);
            emit ready(peerId);
            state = READY;
        }
        else
        {
            if(packetId == 0) {
                //чтение заголовка
                if(bytesAvailable() < 4)
                    return;
                QByteArray header = read(4);
                QDataStream headerStream(&header, QIODevice::ReadOnly);
                headerStream >> packetId >> packetSize;
                qDebug() << "header" << packetId << packetSize;
            }

            if(bytesAvailable() < packetSize)
                return;
            QByteArray body = read(packetSize);
            switch (packetId) {
            case 1:
                QString username(body);
                emit usernameChanged(username);
                break;
            }
            packetId = 0;
            packetSize = 0;
        }
    }
}
