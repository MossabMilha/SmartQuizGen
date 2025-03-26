#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <QFile>

class Encryption {
public:
    static QString encrypt(const QString& input);
    static QString decrypt(const QString& input);

private:
    static const QByteArray secretKey;
};

#endif // ENCRYPTION_H
