#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QNetworkAddressEntry>
#include <QDataStream>

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
     */
    void broadcastReceived(quint64 peerId);
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
};

#endif // BROADCASTER_H
