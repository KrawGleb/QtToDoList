#include "task.h"

Task::Task() {}

Task::Task(QString title, QString description, QDateTime dateTime, int priority) {
    this->title = title;
    this->description = description;
    this->dateTime = dateTime;
    this->priority = priority;
}

Task::Task(QJsonObject json) {
    this->title = json["title"].toString();
    this->description = json["description"].toString();
    this->dateTime = QDateTime::fromString(json["dateTime"].toString(), "yyyy.MM.dd HH:mm:ss");
    this->priority = json["priority"].toInt();
}

Task::Task(QSqlRecord record) {
    this->title = record.value("Title").toString();
    this->description = record.value("Description").toString();
    this->dateTime = QDateTime::fromString(record.value("DateTime").toString(), "yyyy.MM.dd HH:mm:ss");
    this->priority = record.value("priority").toInt();
}

QJsonObject Task::toJson() {
    QJsonObject result;

    result["title"] = this->title;
    result["description"] = this->description;
    result["dateTime"] = this->dateTime.toString("yyyy.MM.dd HH:mm:ss");
    result["priority"] = this->priority;

    return result;
}
