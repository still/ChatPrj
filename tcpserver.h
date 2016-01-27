#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <tcpconnection.h>
/**
 * @brief The TcpServer class Класс сервера tcp-соединений
 */
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject* parent = 0);
signals:
    /**
     * @brief peerConnection Сигнал о новом соединении
     * @param connection Экземпляр соединения
     */
    void peerConnection(TcpConnection* connection);
protected:
    /**
     * @brief incomingConnection Обработка нового соединения
     * @param descriptor Дескриптор сокета
     */
    void incomingConnection(qintptr descriptor);
};

#endif // TCPSERVER_H
