#include "encryption.h"
#include <QCryptographicHash>
#include <QByteArray>

const QByteArray Encryption::secretKey = "Dexter";


QString Encryption::encrypt(const QString& input) {
    QByteArray byteArray = input.toUtf8();

    for (int i = 0; i < byteArray.size(); ++i) {
        byteArray[i] ^= secretKey[i % secretKey.size()];
    }
    return QString(byteArray.toBase64());
}


QString Encryption::decrypt(const QString& input) {
    QByteArray byteArray = QByteArray::fromBase64(input.toUtf8());
    for (int i = 0; i < byteArray.size(); ++i) {
        byteArray[i] ^= secretKey[i % secretKey.size()];
    }
    return QString(byteArray);
}
