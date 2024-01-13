#pragma once
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QPainter>
#include <qpen.h>
#include <QPushButton>
#include "game.h"
#include "EllipseWidget.h"


class QtWidgetsProject : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsProject(QWidget *parent = nullptr);
    ~QtWidgetsProject();
    void setupUi();
    void newGame();
    void clearLayout(QLayout* layout);
    void paintEvent(QPaintEvent* event);

private:
    QGridLayout* layout;
    twixt::Game* game;
};
