#include "logs.h"
#include <QNetworkInterface>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>


namespace Logger{
    void logEntry (QString level,QString message,int user_id, QString ip_address, QString source){
        QSqlQuery query;
        query.prepare(R"(
INSERT INTO public.logs ("level",message,"source","user_id",additional_context, ip_address)
VALUES (:level,:message,:source,:user_id,:additional_context,:ip_address)
)");
        query.bindValue(":user_id",user_id);
        query.bindValue(":level",level);
        query.bindValue(":message",message);
        query.bindValue(":source",source);
        query.bindValue(":ip_address",ip_address);
        query.bindValue(":additional_context", " ");
        if (!query.exec()){
            qDebug() << "Problem so Logger" << query.lastError().text();
        } else {
            qDebug() << "Insert successful!";
        }
    }

    QString getCurrentIPAddress(){
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
    return address.toString();
        }
    return "";
    }

}
