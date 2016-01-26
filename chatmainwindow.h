#ifndef CHATMAINWINDOW_H
#define CHATMAINWINDOW_H

#include <QDebug>

#include <QMainWindow>
#include <QAction>
#include <settingsdialog.h>
#include <profiledialog.h>
#include <peermanager.h>

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

    void managerNewPeer(quint64 peerId, QString username);
private:
    /**
     * @brief setupUi Настройка интерфейса
     */
    void setupUi();

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
};

#endif // CHATMAINWINDOW_H
