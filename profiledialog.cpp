#include "profiledialog.h"
#include "ui_profiledialog.h"

ProfileDialog::ProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileDialog)
{
    ui->setupUi(this);
}

ProfileDialog::~ProfileDialog()
{
    delete ui;
}

void ProfileDialog::setData(Profile &data)
{
    ui->usernameEdit->setText(
                data.username.isEmpty() ? "noname" : data.username);
    ui->keyEdit->setText(data.key);
}

Profile ProfileDialog::getData()
{
    Profile data;
    data.username = ui->usernameEdit->text();
    data.key = ui->keyEdit->text();
    return data;
}
