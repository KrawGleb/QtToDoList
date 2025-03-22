#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include <QFileDialog>
#include <QToolBar>
#include "taskform.h"
#include "task.h"
#include "taskitem.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addTaskButton_clicked();

    void onCancelButtonClicked();
    void onCloseEditForm(TaskForm* taskForm, Task* task);

    void onAddButtonClicked(Task* task);
    void onTaskItemDelete(TaskItem* taskItem);
    void onTaskItemEdit(TaskItem* taskItem, Task* sourceTask);

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

private:
    Ui::MainWindow *ui;
    TaskForm* taskForm;
    QMenuBar* toolbar;

    void deleteForm();
    void connectTaskItem(TaskItem* taskItem);
    void showToolBar();
};
#endif // MAINWINDOW_H
