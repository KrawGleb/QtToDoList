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
