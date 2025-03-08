#ifndef TASK_H
#define TASK_H

#include <qstring.h>
#include <qdatetime.h>

class Task
{
public:
    Task();
    Task(QString title, QString description, QDateTime dateTime, int priority);

    QString title;
    QString description;
    QDateTime dateTime;
    int priority;
};

#endif // TASK_H
