#include "taskform.h"
#include "ui_taskform.h"

TaskForm::TaskForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskForm)
{
    ui->setupUi(this);
}

TaskForm::~TaskForm()
{
    delete ui;
}

void TaskForm::on_cancelButton_clicked()
{
    emit onCancelButtonClicked();
}

void TaskForm::on_addTaskButton_clicked()
{
    Task* task = new Task(
        ui->title->text(),
        ui->description->toPlainText(),
        ui->dateTimeEdit->dateTime(),
        ui->priority->value());

    emit onAddButtonClicked(task);
}

