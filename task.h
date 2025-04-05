#ifndef TASK_H
#define TASK_H

#include <qstring.h>
#include <qdatetime.h>
#include <qjsonobject.h>
#include <qsqlrecord.h>

class Task
{
public:
    Task();
    Task(QString title, QString description, QDateTime dateTime, int priority);
    Task(QJsonObject json);
    Task(QSqlRecord record);

    QString title;
    QString description;
    QDateTime dateTime;
    int priority;

    QJsonObject toJson();
};

#endif // TASK_H
