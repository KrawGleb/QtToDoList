#ifndef TASKFORM_H
#define TASKFORM_H

#include "task.h"
#include <QWidget>

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(Task* sourceTask = nullptr, QWidget *parent = nullptr);
    ~TaskForm();

private:
    Ui::TaskForm *ui;
    Task* sourceTask;

signals:
    void onCancelButtonClicked();
    void onCancelEditButtonClicked(TaskForm* taskForm, Task* task);

    void onAddButtonClicked(Task* task);
    void onEditButtonClicked(TaskForm* taskForm, Task* task);

private slots:
    void on_cancelButton_clicked();
    void on_addTaskButton_clicked();
};

#endif // TASKFORM_H
