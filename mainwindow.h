#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qmessagebox.h>
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

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    TaskForm* taskForm = nullptr;
    QString openedFile;

    void deleteForm();
    void connectTaskItem(TaskItem* taskItem);
    bool writeToFile(QString fileName, QFlags<QIODevice::OpenModeFlag> mode);
};
#endif // MAINWINDOW_H
