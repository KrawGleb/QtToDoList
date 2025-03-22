#ifndef TASK_H
#define TASK_H

#include <QJsonObject>
#include <qstring.h>
#include <qdatetime.h>

class Task
{
public:
    Task();
    Task(QString title, QString description, QDateTime dateTime, int priority);
    Task(QJsonObject json);

    QString title;
    QString description;
    QDateTime dateTime;
    int priority;
};

#endif // TASK_H
