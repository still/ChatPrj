#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>
#include <QDataStream>

/**
 * @brief The TcpConnection class Класс постоянного p2p соединения
 */
class TcpConnection : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpConnection(QObject* parent = 0);
    ~TcpConnection();

    /**
     * @brief setCurrentId Установка идентификатора
     * @param id Идентификатор
     */
    void setCurrentId(quint64 id);
    /**
     * @brief getCurrentId Получение идентификатора
     * @return Идентификатор
     */
    quint64 getCurrentId();
signals:
    /**
     * @brief ready Соединение установлено, готово к использованию
     * @param peerId
     */
    void ready(quint64 peerId);
private slots:
    /**
     * @brief handshake Отсылка идентификатора
     */
    void handshake();
    /**
     * @brief readyReadHandler Чтение из сокета
     */
    void readyReadHandler();
private:
    /**
     * @brief currentId Идентификатор
     */
    quint64 currentId;

    /**
     * @brief isHandhaked Флаг указывающий о отсылке идентификатора
     */
    bool isHandhaked;
};

#endif // TCPCONNECTION_H
