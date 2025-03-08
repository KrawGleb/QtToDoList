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

private:
    Ui::TaskItem *ui;
};

#endif // TASKITEM_H
