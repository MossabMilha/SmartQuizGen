#include "sendemail.h"
#include <QProcess>
#include <QByteArray>
#include <QDebug>

SendEmail::SendEmail() {}

QString SendEmail::base64UrlEncode(const QString &message) {
    QByteArray bytes = message.toUtf8().toBase64(QByteArray::Base64Encoding | QByteArray::OmitTrailingEquals);
    return bytes.replace('+', '-').replace('/', '_');
}

bool SendEmail::sendEmailWithCode(const QString &email, int code, const QString &accessToken) {
    QString subject = "Your Password Reset Code";
    QString body = QString("Hello,\n\nYour password reset code is: %1\nIt will expire in 10 minutes.\n\nRegards,\nSmartQuizGen Team").arg(code);

    QString rawEmail = QString(
                           "To: %1\r\n"
                           "Subject: %2\r\n"
                           "\r\n"
                           "%3"
                           ).arg(email, subject, body);

    QString encodedMessage = base64UrlEncode(rawEmail);

    QStringList args;
    args << "-X" << "POST"
         << "-H" << QString("Authorization: Bearer %1").arg(accessToken)
         << "-H" << "Content-Type: application/json"
         << "-d" << QString("{\"raw\":\"%1\"}").arg(encodedMessage)
         << "https://gmail.googleapis.com/gmail/v1/users/me/messages/send";

    QProcess curl;
    args.prepend("-s");
    curl.start("curl", args);
    curl.waitForFinished();

    QString result = curl.readAllStandardOutput();
    QString error = curl.readAllStandardError();

    if (!error.isEmpty()) {
        qDebug() << "Curl Error:" << error;
        return false;
    }

    qDebug() << "Email Sent Response:" << result;
    return true;
}
