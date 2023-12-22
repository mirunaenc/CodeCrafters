#include "Twixt.h"
#include <QWidget>
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
    Ui::GameInterface gameInterface; // Inițializează interfața GameInterface
    QWidget* gameWidget = new QWidget(); // Creează un nou widget

    gameInterface.setupUi(gameWidget); // Setează interfața GameInterface pentru noul widget

    setCentralWidget(gameWidget); // Setează noul widget ca centralWidget în fereastra principală
}