#include "dbmanager.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

bool dbmanager::connect(const QString &host, int port,
                        const QString &dbName, const QString &user,
                        const QString &password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "ERROR, Neuspesna konekcija";
        qDebug() << db.lastError().text();
        return false;
    }

    qDebug() << "Konekcijata e uspeshna";
    return true;
}
