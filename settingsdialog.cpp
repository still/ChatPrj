#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    //получаем список интерфейсов, заполняем выпадающий список
    fillInterfaces();
    ui->interfaceCmb->addItems(nameList);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setData(Settings &data)
{
    int index = indexOfInterface(data.entry);
    if(index = -1 && entryList.size() > 0)
        index = 0;
    ui->interfaceCmb->setCurrentIndex(index);
}

Settings SettingsDialog::getData()
{
    Settings data;
    int currentIndex = ui->interfaceCmb->currentIndex();
    data.entry = currentIndex >= 0 ? entryList.at(currentIndex) : QNetworkAddressEntry();
    return data;
}

void SettingsDialog::fillInterfaces()
{
    entryList.clear();
    nameList.clear();
    QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
    QNetworkInterface eth;
    //цикл по интерфейсам
    foreach(eth, allInterfaces)
    {
        QList<QNetworkAddressEntry> addressEntries = eth.addressEntries();
        QNetworkAddressEntry entry;
        //цикл по адресам
        foreach(entry, addressEntries)
        {
            //только протокол IPv4, исключаем петлю
            if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol
                    && entry.ip() != QHostAddress(QHostAddress::LocalHost))
            {
                entryList << entry;
                nameList << tr("%1 %2").arg(eth.humanReadableName())
                           .arg(entry.ip().toString());
            }
        }
    }
}

int SettingsDialog::indexOfInterface(QNetworkAddressEntry &entry)
{
    return entryList.indexOf(entry);
}
