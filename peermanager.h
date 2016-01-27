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
    ~PeerManager();

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
    /**
     * @brief usernameChanged Сигнал изменения имени пира
     * @param peerId Идентификатор пира
     * @param username Новое имя
     */
    void usernameChanged(quint64 peerId, QString username);

    /**
     * @brief messageGetted Сигнал получения нового сообщения
     * @param peerId Идентификатор пира
     * @param message Текст сообщения
     */
    void messageGetted(quint64 peerId, QString message);
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

    /**
     * @brief sendUsername Отсылка имени текущего пира
     * @param username Новое имя
     * @param peerId Идентификатор пира, которому нужно отослать,
     * 0 - всем пирам
     */
    void sendUsername(QString username, quint64 peerId = 0);

    /**
     * @brief sendMessage Отсылка сообщения пиру
     * @param message Текст сообщения
     * @param peerId Идентификатор сообщения
     */
    void sendMessage(QString message, quint64 peerId);
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

    /**
     * @brief changeUsername Обработчик изменения имени пира
     * @param username Новое имя пира
     */
    void changeUsername(QString username);

    /**
     * @brief getMessage Обработчик получения сообщения
     * @param message Текст сообщения
     */
    void getMessage(QString message);
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
