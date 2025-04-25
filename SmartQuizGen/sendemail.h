#ifndef SENDEMAIL_H
#define SENDEMAIL_H
#include <QString>

class SendEmail
{
    QString base64UrlEncode(const QString &message);
public:
    SendEmail();
     bool sendEmailWithCode(const QString &email, int code, const QString &accessToken);
};

#endif // SENDEMAIL_H
