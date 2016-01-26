#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QNetworkAddressEntry>
#include <QDataStream>

const int MSG_TICK      = 1;
const int MSG_MESSAGE   = 2;

/**
 * @brief The Broadcaster class Класс реализующий функционал обнаружения пиров
 */
class Broadcaster : public QObject
{
    Q_OBJECT
public:
    explicit Broadcaster(QObject *parent = 0);

signals:
    /**
     * @brief broadcastReceived Сигнал получения широковещательного сообщения
     * @param peerId Идентификатор пира
     * @param peerId Имя пира
     */
    void broadcastReceived(quint64 peerId, QString username);
public slots:
    /**
     * @brief start Запуск широковещательных сообщений
     * @param entry Сетевой интерфейс
     * @param broadcastPrt Порт широковещательных сообщений
     * @param serverPrt Порт сервера tcp-соединений
     * @param msec Интервал таймера отсылки широковещательных сообщений
     * @return Идентификатор в случае удачи, иначе - 0
     */
    quint64 start(QNetworkAddressEntry entry, quint16 broadcastPrt, quint16 serverPrt, int msec);

    /**
     * @brief stop Остановка широковещательных сообщений
     */
    void stop();

    void setUsername(const QString& username);

private slots:
    /**
     * @brief timerTimeout Обработчик таймера, отсылка сообщений
     */
    void timerTimeout();
    /**
     * @brief socketReadyRead Чтение сообщений
     */
    void socketReadyRead();
private:
    /**
     * @brief socket Сокет
     */
    QUdpSocket* socket;

    /**
     * @brief timer Таймер отсылки пакетов
     */
    QTimer* timer;

    /**
     * @brief currentEntry Текущий интерфейс
     */
    QNetworkAddressEntry currentEntry;

    /**
     * @brief broadcastPort Порт широковещательных сообщений
     */
    quint16 broadcastPort;

    /**
     * @brief currentId Идентификатор хостового пира (ip << 16) + порт сервера
     */
    quint64 currentId;

    /**
     * @brief username Nickname
     */
    QString username;
};

#endif // BROADCASTER_H
