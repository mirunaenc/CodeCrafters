#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Twixt.h"

class Twixt : public QMainWindow
{
    Q_OBJECT

public:
    Twixt(QWidget *parent = nullptr);
    ~Twixt();

private:
    Ui::TwixtClass ui;
};
