#include "QtWidgetsProject.h"

QtWidgetsProject::QtWidgetsProject(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    layout = new QGridLayout;
    centralWidget->setLayout(layout);
    game = new twixt::Game();

    setupUi();
}

QtWidgetsProject::~QtWidgetsProject()
{}

void QtWidgetsProject::setupUi()
{
    QPushButton* newGameButton = new QPushButton("New Game", this);
    connect(newGameButton, &QPushButton::clicked, this, &Window::newGame);
    layout->addWidget(newGameButton, 0, 0);
}
