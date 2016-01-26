#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QObject>
#include <broadcaster.h>
#include <QTcpServer>
#include <QTcpSocket>

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
    void newPeer(quint64 peerId, QString username);
public slots:
    void setUsername(const QString& username);
    void start(QNetworkAddressEntry entry, quint16 broadcastPrt, int msec);
    void stop();

private slots:
    void broadcasterBroadcastReceived(quint64 peerId, QString username);
    void peerTimeout();
private:
    /**
     * @brief broadcaster Рассылка широковещательных пакетов
     */
    Broadcaster* broadcaster;

    QTcpServer* server;

    QMap<quint64, QTimer*> peerMap;
};

#endif // PEERMANAGER_H
