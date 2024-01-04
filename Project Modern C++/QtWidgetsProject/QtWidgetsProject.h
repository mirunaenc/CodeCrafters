#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsProject.h"

class QtWidgetsProject : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsProject(QWidget *parent = nullptr);
    ~QtWidgetsProject();

private:
    Ui::QtWidgetsProjectClass ui;
};
