#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // showToolBar();
}

MainWindow::~MainWindow()
{
    delete this->toolbar;
    delete ui;
}

void MainWindow::showToolBar()
{
    this->toolbar = new QMenuBar();

    QMenu* fileMenu = menuBar()->addMenu("File");

    QAction* saveAsAction = new QAction("Save as...");
    QAction* loadFrom = new QAction("Load from...");

    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(loadFrom);
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

    if (this->taskForm != nullptr) {
        ui->formLayout->removeWidget(this->taskForm);

        delete this->taskForm;
    }
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

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.json");
    if (fileName.isEmpty()) return;

    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly)) {
        int count = 0;
        QJsonDocument root = QJsonDocument::fromJson(file.readAll());

        foreach(QJsonValue value, root.array()) {
            QJsonObject object = value.toObject();
            Task* task = new Task(object);
            onAddButtonClicked(task);
            count++;
        }

        file.close();

        QMessageBox::information(this, "Done", QString("Loaded %1 items from %2").arg(QString::number(count), fileName));
    }
    else {
        QMessageBox::critical(this, "Error", QString("Failed to open %1").arg(fileName));
    }

}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as ...", QDir::homePath(), "*.json");
    if (fileName.isEmpty()) return;

    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly))
    {
        int count = 0;
        QJsonDocument root;
        QJsonArray jsonArray;
        foreach (auto child, ui->scrollArea->widget()->findChildren<TaskItem*>()) {
            jsonArray.push_back(child->toJson());
            count++;
        }

        root.setArray(jsonArray);
        file.write(root.toJson());

        file.close();

        QMessageBox::information(this, "Done", QString("Saved %1 items to %2").arg(QString::number(count), fileName));
    }
    else {
        QMessageBox::critical(this, "Error", QString("Failed to open %1").arg(fileName));
    }
}

