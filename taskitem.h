#ifndef TASKITEM_H
#define TASKITEM_H

#include <QWidget>
#include "task.h"

namespace Ui {
class TaskItem;
}

class TaskItem : public QWidget
{
    Q_OBJECT

public:
    explicit TaskItem(Task* sourceTask, QWidget *parent = nullptr);
    ~TaskItem();

signals:
    void onTaskItemDelete(TaskItem* item);
    void onTaskItemEdit(TaskItem* item, Task* sourceTask);

private slots:
    void on_deleteButton_clicked();

    void on_editButton_clicked();

private:
    Ui::TaskItem *ui;
    Task* sourceTask;
};

#endif // TASKITEM_H
