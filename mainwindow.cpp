#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addTaskButton_clicked()
{
    ui->addFormLayout->setVisible(false);

    TaskForm* taskForm = new TaskForm();
    ui->formLayout->addWidget(taskForm);

    connect(taskForm, &TaskForm::onCancelButtonClicked, this, &MainWindow::onCancelButtonClicked);
    connect(taskForm, &TaskForm::onAddButtonClicked, this, &MainWindow::onAddButtonClicked);
    this->taskForm = taskForm;
}

void MainWindow::onCancelButtonClicked() {
    this->deleteForm();
}

void MainWindow::onCloseEditForm(TaskForm* taskForm, Task* task) {
    TaskItem* taskItem = new TaskItem(task, this);

    this->connectTaskItem(taskItem);

    ui->scrollArea->widget()->layout()->replaceWidget(taskForm, taskItem);
    delete taskForm;
}

void MainWindow::onAddButtonClicked(Task* task) {
    this->deleteForm();

    TaskItem* taskItem = new TaskItem(task, this);

    ui->scrollArea->widget()->layout()->addWidget(taskItem);

    this->connectTaskItem(taskItem);
}

void MainWindow::deleteForm() {
    ui->addFormLayout->setVisible(true);
    ui->formLayout->removeWidget(this->taskForm);

    delete this->taskForm;
}

void MainWindow::onTaskItemDelete(TaskItem* taskItem)
{
    ui->scrollArea->widget()->layout()->removeWidget(taskItem);

    delete taskItem;
}

void MainWindow::onTaskItemEdit(TaskItem* taskItem, Task* sourceTask) {
    TaskForm* taskForm = new TaskForm(sourceTask);

    ui->scrollArea->widget()->layout()->replaceWidget(taskItem, taskForm);
    delete taskItem;

    connect(taskForm, &TaskForm::onCancelEditButtonClicked, this, &MainWindow::onCloseEditForm);
    connect(taskForm, &TaskForm::onEditButtonClicked, this, &MainWindow::onCloseEditForm);
}

void MainWindow::connectTaskItem(TaskItem* taskItem) {
    connect(taskItem, &TaskItem::onTaskItemDelete, this, &MainWindow::onTaskItemDelete);
    connect(taskItem, &TaskItem::onTaskItemEdit, this, &MainWindow::onTaskItemEdit);
}
