#include "taskform.h"
#include "ui_taskform.h"

TaskForm::TaskForm(Task* task, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskForm)
{
    ui->setupUi(this);

    this->sourceTask = task;

    if (task != nullptr) {
        ui->title->setText(task->title);
        ui->description->setPlainText(task->description);
        ui->dateTimeEdit->setDateTime(task->dateTime);
        ui->priority->setValue(task->priority);

        ui->addTaskButton->setText("Update");
    }
}

TaskForm::~TaskForm()
{
    delete ui;
}

void TaskForm::on_cancelButton_clicked()
{
    if (this->sourceTask != nullptr) {
        emit onCancelEditButtonClicked(this, this->sourceTask);
    }
    else {
        emit onCancelButtonClicked();
    }
}

void TaskForm::on_addTaskButton_clicked()
{
    if (this->sourceTask != nullptr) {
        this->sourceTask->title = ui->title->text();
        this->sourceTask->description = ui->description->toPlainText();
        this->sourceTask->dateTime = ui->dateTimeEdit->dateTime();
        this->sourceTask->priority  =ui->priority->value();

        emit onEditButtonClicked(this, this->sourceTask);
    }
    else {
        Task* task = new Task(
            ui->title->text(),
            ui->description->toPlainText(),
            ui->dateTimeEdit->dateTime(),
            ui->priority->value());

        emit onAddButtonClicked(task);
    }
}

