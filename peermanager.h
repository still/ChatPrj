#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QObject>
#include <broadcaster.h>
#include <QTcpSocket>

/**
 * @brief The PeerManager class Класс управления пирами
 */
class PeerManager : public QObject
{
    Q_OBJECT
public:
    explicit PeerManager(QObject *parent = 0);

signals:

public slots:
    void start(QNetworkAddressEntry entry, quint16 broadcastPrt, int msec);
    void stop();

private slots:
    void broadcasterBroadcastReceived(quint64 peerId);
private:
    /**
     * @brief broadcaster Рассылка широковещательных пакетов
     */
    Broadcaster* broadcaster;

    QMap<quint64, QTcpSocket*> peerMap;
};

#endif // PEERMANAGER_H
