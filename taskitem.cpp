#include "taskitem.h"
#include "ui_taskitem.h"

TaskItem::TaskItem(Task* sourceTask, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskItem)
{
    ui->setupUi(this);

    ui->label->setText(sourceTask->title);
    ui->description->setText(sourceTask->description);
}

TaskItem::~TaskItem()
{
    delete ui;
}
