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
#include <QSpinBox>
#include "game.h"
#include "GameFileManager.h"
#include "EllipseWidget.h"
#include "WinnerDialog.h"


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
    void onEllipseClick();
    void drawBridges(QPainter& painter);
    void checkWinner();
    void onSaveClick();
    void onEndTurnClick();

private:
    QGridLayout* layout;
    twixt::Game* game;
    QLabel* boardSizeLabel;
    QLabel* pylonsLabel;
    QLabel* bridgesLabel;
    QSpinBox* boardSizeSpinBox;
    QSpinBox* pylonsSpinBox;
    QSpinBox* bridgesSpinBox;
};
