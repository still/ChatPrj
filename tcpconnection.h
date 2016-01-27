#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>
#include <QDataStream>

enum ConnectionState {
    WAIT,   //ожидание handshake
    READY   //ожидание пакетов
};

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

    /**
     * @brief sendUsername Отсылка имени текущего пира
     * @param username Имя текущего пира
     */
    void sendUsername(const QString& username);

    /**
     * @brief sendMessage Отсылка сообщения
     * @param message Текст сообщения
     */
    void sendMessage(const QString& message);
signals:
    /**
     * @brief ready Соединение установлено, готово к использованию
     * @param peerId
     */
    void ready(quint64 peerId);

    /**
     * @brief usernameChanged Сигнал об изменении имени пира
     * @param username Имя пира
     */
    void usernameChanged(QString username);

    /**
     * @brief messageGetted Сигнал о получении сообщения
     * @param message Текст сообщения
     */
    void messageGetted(QString message);
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

    /**
     * @brief state Текущее состояние соединения
     */
    ConnectionState state;

    /**
     * @brief packetId Идентификатор ожидаемого пакета
     */
    quint16 packetId;
    /**
     * @brief packetSize Размер ожидаемого пакета
     */
    quint16 packetSize;
};

#endif // TCPCONNECTION_H
