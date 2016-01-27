#ifndef CHATMAINWINDOW_H
#define CHATMAINWINDOW_H

#include <QDebug>

#include <QMainWindow>
#include <QAction>
#include <settingsdialog.h>
#include <profiledialog.h>
#include <peermanager.h>
#include <QStringListModel>
#include <encryption.h>

namespace Ui {
class ChatMainWindow;
}
/**
 * @brief The ChatMainWindow class Класс главного окна чата
 */
class ChatMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatMainWindow(QWidget *parent = 0);
    ~ChatMainWindow();
public slots:
    /**
     * @brief settingsActionTriggered Обработчик settingsAction,
     * отображение и обработка формы настроек
     */
    void settingsActionTriggered();
    /**
     * @brief profileActionTriggered Обработчик profileAction,
     * отображение и обработка формы профиля
     */
    void profileActionTriggered();
    /**
     * @brief messageBtnClicked Обработчик кнопки отсылки сообщения
     */
    void messageBtnClicked();
    /**
     * @brief peerListRowChanged Обработчик выбора текущего собеседника
     * @param index Индекс из peerList
     */
    void peerListRowChanged(int index);

    /**
     * @brief addPeer Добавление нового пира в список пиров
     * @param peerId Идентификатор пира
     */
    void addPeer(quint64 peerId);

    /**
     * @brief deletePeer Удаление пира из списка
     * @param peerId Идентификатор пира
     */
    void deletePeer(quint64 peerId);

    /**
     * @brief changePeerUsername Изменение имени пира
     * @param peerId Идентификатор пира
     * @param username Новое имя
     */
    void changePeerUsername(quint64 peerId, QString username);

    /**
     * @brief getPeerMessage Добавление нового сообщения
     * @param peerId Идентификатор пира
     * @param message Текст сообщения
     */
    void getPeerMessage(quint64 peerId, QString message);
private:
    /**
     * @brief setupUi Настройка интерфейса
     */
    void setupUi();

    /**
     * @brief indexByPeerId Поиск по идентификатору индекса в списке пиров
     * @param peerId Идентификатор
     * @return Индекс
     */
    int indexByPeerId(quint64 peerId);

    /**
     * @brief usenameByPeerId Получение имени по идентификатору пира
     * @param peerId Идентификатор пира
     * @return Имя пира
     */
    QString usenameByPeerId(quint64 peerId);

    /**
     * @brief enableMessaging Активирование гуя для отправки сообщиний
     * @param ison Флаг активации
     */
    void enableMessaging(bool ison);

    /**
     * @brief appendMessage Добавление сообщения в конец модели
     * @param message Сообщение
     * @param peerId Идентификатор пира
     */
    void appendMessage(QString message, quint64 peerId);
private:
    Ui::ChatMainWindow *ui;
    /**
     * @brief settingsAction QAction для формы настроек
     */
    QAction* settingsAction;
    /**
     * @brief profileAction QAction для формы профиля
     */
    QAction* profileAction;

    /**
     * @brief settings Настройки приложения
     */
    Settings settings;

    /**
     * @brief profile Настройки профиля
     */
    Profile profile;

    /**
     * @brief manager Управление соединениями
     */
    PeerManager* manager;

    /**
     * @brief peerMessages Сообщения пиров
     */
    QMap<quint64, QStringListModel*> peerMessages;
};

#endif // CHATMAINWINDOW_H
