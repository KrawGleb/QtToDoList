#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionSave->setEnabled(false);
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
    if (this->taskForm != nullptr) {
        ui->formLayout->removeWidget(this->taskForm);

        delete this->taskForm;
        this->taskForm = nullptr;
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
    QString fileName = QFileDialog::getOpenFileName(this, "Open", QDir::homePath(), "*.json, *.db");
    if (fileName.isEmpty()) return;

    QString format = fileName.split('.').last();

    if (format == "json") {
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly)) {
            this->openedFile = fileName;

            foreach(TaskItem* taskItem, ui->scrollArea->widget()->findChildren<TaskItem*>()) {
                onTaskItemDelete(taskItem);
            }

            ui->actionSave->setEnabled(true);

            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            int count = 0;

            foreach(QJsonValue value, doc.array()) {
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
    else if (format == "db") {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(fileName);
        if (db.open()) {
            QSqlTableModel* tableModel = new QSqlTableModel(this, db);
            tableModel->setTable("Tasks");
            tableModel->select();
            int rowCount = tableModel->rowCount();

            for (int i = 0; i < rowCount; ++i) {
                qDebug() << tableModel->record(i).value("Title").toString();
            }

            delete tableModel;
        }
        else {
            QMessageBox::critical(this, "Error", QString("Failed to open %1").arg(fileName));
            return;
        }

    }
}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as...", QDir::homePath(), "*.json");
    if (fileName.isEmpty()) return;

    if (writeToFile(fileName, QIODevice::WriteOnly)) {
        QMessageBox::information(this, "Done", QString("Saved items to %2").arg(fileName));
    }
    else {
        QMessageBox::critical(this, "Error", QString("Failed to open %1").arg(fileName));
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (this->openedFile.isEmpty()) return;

    if (writeToFile(this->openedFile, QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::information(this, "Done", QString("Saved items to %2").arg(this->openedFile));
    }
    else {
        QMessageBox::critical(this, "Error", QString("Failed to open %1").arg(this->openedFile));
    }
}

bool MainWindow::writeToFile(QString fileName, QFlags<QIODevice::OpenModeFlag> mode) {
    QFile file(fileName);
    if (file.open(mode)) {
        int count = 0;
        QJsonArray array;

        foreach(TaskItem* taskItem, ui->scrollArea->widget()->findChildren<TaskItem*>()) {
            array.push_back(taskItem->sourceTask->toJson());
            count++;
        }

        QJsonDocument root;
        root.setArray(array);

        file.write(root.toJson());
        file.close();

        return true;
    }
    else {
        return false;
    }
}

