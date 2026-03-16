#ifndef LOGS_H
#define LOGS_H
#include <QString>


namespace Logger {
void logEntry(QString level,QString message,int user_id,QString ip_address, QString source);
QString getCurrentIPAddress();
}

#endif // LOGS_H
