#include "taskitem.h"
#include "ui_taskitem.h"

TaskItem::TaskItem(Task* sourceTask, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskItem)
{
    ui->setupUi(this);

    this->sourceTask = sourceTask;

    ui->title->setText(sourceTask->title);
    ui->description->setText(sourceTask->description);
}

TaskItem::~TaskItem()
{
    delete ui;
}

void TaskItem::on_deleteButton_clicked()
{
    delete this->sourceTask;
    emit onTaskItemDelete(this);
}

void TaskItem::on_editButton_clicked()
{
    emit onTaskItemEdit(this, this->sourceTask);
}

QJsonObject TaskItem::toJson()
{
    QJsonObject jsonObject;
    jsonObject["title"] = this->sourceTask->title;
    jsonObject["description"] = this->sourceTask->description;
    jsonObject["dateTime"] = this->sourceTask->dateTime.toString("yyyy.MM.dd HH:mm:ss");
    jsonObject["priority"] = this->sourceTask->priority;

    return jsonObject;
}
