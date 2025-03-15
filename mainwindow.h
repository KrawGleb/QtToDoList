#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    TaskForm* taskForm;

    void deleteForm();
    void connectTaskItem(TaskItem* taskItem);
};
#endif // MAINWINDOW_H
