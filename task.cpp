#include "task.h"

Task::Task() {}

Task::Task(QString title, QString description, QDateTime dateTime, int priority) {
    this->title = title;
    this->description = description;
    this->dateTime = dateTime;
    this->priority = priority;
}
