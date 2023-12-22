#include "Twixt.h"
#include <QWidget>
#include "ui_GameInterface.h"
#include "GameInterface.h"


Twixt::Twixt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
}

Twixt::~Twixt()
{}

void Twixt::on_pushButton_clicked() {
    GameInterface gameInterface;
    gameInterface.setModal(true);
    gameInterface.exec();
}