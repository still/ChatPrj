#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QObject>
#include <broadcaster.h>
#include <tcpserver.h>
#include <tcpserver.h>

/**
 * @brief The PeerManager class Класс управления пирами
 */
class PeerManager : public QObject
{
    Q_OBJECT
public:
    explicit PeerManager(QObject *parent = 0);

signals:
    /**
     * @brief broadcastPeerConnection Сигнал о входящем соединии
     * @param connection Экземпляр соединения
     */
    void broadcastPeerConnection(TcpConnection *connection);
    /**
     * @brief peerToAdd Сигнал о новом пире в сети
     * @param peerId Идентификатор пира
     */
    void peerToAdd(quint64 peerId);
    /**
     * @brief peerToDelete Сигнал о уходе пира из сети
     * @param peerId Идентификатор пира
     */
    void peerToDelete(quint64 peerId);
public slots:
    /**
     * @brief start Запуск tcp-сервера и широковещательных сообщений
     * @param entry Сетевой интерфейс
     * @param broadcastPrt Порт широковещательных сообщений
     * @param msec Интервал отсылки широковещательных сообщений
     */
    void start(QNetworkAddressEntry entry, quint16 broadcastPrt, int msec);
    /**
     * @brief stop Остановка tcp-сервера и широковещательных сообщений
     */
    void stop();

private slots:
    /**
     * @brief broadcasterBroadcastReceived Обработка широковещательного
     * сообщения
     * @param peerId Идентификатор пира
     */
    void broadcasterBroadcastReceived(quint64 peerId);
    /**
     * @brief peerConnection Обработка новых соединений
     * @param connection Экземпляр соединения
     */
    void peerConnection(TcpConnection* connection);
    /**
     * @brief connectionReady Обработка готового соединения
     * @param peerId Идентификатор пира
     */
    void connectionReady(quint64 peerId);
    /**
     * @brief connectionDisconnected Удаление пира
     */
    void connectionDisconnected();
private:
    /**
     * @brief broadcaster Рассылка широковещательных пакетов
     */
    Broadcaster* broadcaster;

    /**
     * @brief server Tcp-сервер входящих соединений
     */
    TcpServer* server;

    /**
     * @brief peerMap Соединения с пирами
     */
    QMap<quint64, TcpConnection*> peerMap;
};

#endif // PEERMANAGER_H
