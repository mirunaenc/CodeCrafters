#pragma once

#include <QMainWindow>
#include "ui_GameInterface.h"
#include <QDialog>

class GameInterface : public QMainWindow
{
	Q_OBJECT

public:
	GameInterface(QWidget *parent = nullptr);
	~GameInterface();

private:
	Ui::GameInterfaceClass ui;
};
