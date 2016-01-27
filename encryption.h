#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>
#include <QDebug>

inline QString encodeXOR(const QString &string, const QString& key)
{
    if(string.size() == 0 || key.size() == 0)
        return QString();
    QByteArray encryptedArray;
    QByteArray stringArray(string.toUtf8());
    QByteArray keyArray(key.toUtf8());
    for(int i = 0; i < stringArray.size(); i++) {
        encryptedArray.append(stringArray.at(i) ^ keyArray.at(i % keyArray.size()));
    }
    return QString::fromLatin1(encryptedArray.toBase64());
}

inline QString decodeXOR(const QString &string, const QString& key)
{
    if(string.size() == 0 || key.size() == 0)
        return QString();
    QByteArray encryptedArray;
    QByteArray stringArray = QByteArray::fromBase64(string.toLatin1());
    QByteArray keyArray(key.toUtf8());
    for(int i = 0; i < stringArray.size(); i++) {
        encryptedArray.append(stringArray.at(i) ^ keyArray.at(i % keyArray.size()));
    }
    return QString::fromUtf8(encryptedArray);
}

#endif // ENCRYPTION_H
