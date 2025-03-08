#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tasks = new vector<Task*>();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete[] tasks;
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

void MainWindow::onAddButtonClicked(Task* task) {
    this->tasks->push_back(task);
    this->deleteForm();

    TaskItem* taskItem = new TaskItem(task, this);
}

void MainWindow::deleteForm() {
    ui->addFormLayout->setVisible(true);
    ui->formLayout->removeWidget(this->taskForm);

    delete this->taskForm;
}
