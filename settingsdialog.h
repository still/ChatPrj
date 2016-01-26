#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QNetworkAddressEntry>

//структура для хранения настроек
typedef struct
{
    QNetworkAddressEntry entry;     //сетевой интерфейс
} Settings;

namespace Ui {
class SettingsDialog;
}

/**
 * @brief The SettingsDialog class Форма настроек
 */
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    /**
     * @brief setData Установка параметров
     * @param data Параметры
     */
    void setData(Settings& data);

    /**
     * @brief getData Получение измененных параметров
     * @return Параметры
     */
    Settings getData();
private:
    /**
     * @brief fillInterfaces Заполнение списков доступных интерфейсов и их имен
     */
    void fillInterfaces();

    /**
     * @brief indexOfInterface Получение индекса интерфейса
     * @param entry Ссылка на искомый интерфейс
     * @return Индекс в списке, -1 - если не найден
     */
    int indexOfInterface(QNetworkAddressEntry& entry);
private:
    Ui::SettingsDialog *ui;
    /**
     * @brief entryList Список доступных интерфейсов
     */
    QList<QNetworkAddressEntry> entryList;
    /**
     * @brief nameList Список названий доступных интерфейсов
     */
    QStringList nameList;
};

#endif // SETTINGSDIALOG_H
