#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Twixt.h"
#include "ui_GameInterface.h"
class Twixt : public QMainWindow
{
    Q_OBJECT

public:
    Twixt(QWidget *parent = nullptr);
    ~Twixt();

private:
    Ui::TwixtClass ui;

private slots:
    void on_pushButton_clicked();

};
