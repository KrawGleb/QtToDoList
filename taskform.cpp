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
