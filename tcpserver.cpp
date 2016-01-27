#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{

}

void TcpServer::incomingConnection(qintptr descriptor)
{
    TcpConnection* connection = new TcpConnection(this);
    connection->setSocketDescriptor(descriptor);
    emit peerConnection(connection);
}
