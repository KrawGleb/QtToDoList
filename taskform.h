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
    explicit TaskForm(QWidget *parent = nullptr);
    ~TaskForm();

private:
    Ui::TaskForm *ui;

signals:
    void onCancelButtonClicked();
    void onAddButtonClicked(Task* task);

private slots:
    void on_cancelButton_clicked();
    void on_addTaskButton_clicked();
};

#endif // TASKFORM_H
