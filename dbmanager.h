#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>

class dbmanager
{
public:
    static bool connect(const QString &host, int port,
                        const QString &dbName, const QString &user,
                        const QString &password);
};

#endif // DBMANAGER_H
