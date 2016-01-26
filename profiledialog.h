#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>

//структура для хранения параметров профиля
typedef struct
{
    QString username;       //имя пользователя
    QString key;            //ключ шифрования
} Profile;

namespace Ui {
class ProfileDialog;
}

/**
 * @brief The ProfileDialog class Форма параметров профиля
 */
class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(QWidget *parent = 0);
    ~ProfileDialog();

    /**
     * @brief setData Установка параметров
     * @param data Параметры
     */
    void setData(Profile &data);

    /**
     * @brief getData Получение измененных параметров
     * @return Параметры
     */
    Profile getData();

private:
    Ui::ProfileDialog *ui;
};

#endif // PROFILEDIALOG_H
