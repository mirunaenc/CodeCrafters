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
    connect(newGameButton, &QPushButton::clicked, this, &QtWidgetsProject::newGame);
    layout->addWidget(newGameButton, 0, 0);
}

void QtWidgetsProject::newGame()
{
    clearLayout(layout);
    update();
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i = 0; i < game->getGameBoard().getSize() /*g->GetWidth()*/; i++)
    {
        for (int j = 0; j < game->getGameBoard().getSize() /*g->GetWidth()*/; j++)
        {
            EllipseWidget* ellipseWidget = new EllipseWidget();
            ellipseWidget->setFixedSize(30, 30);
            ellipseWidget->setColor(Qt::white);
            ellipseWidget->setProperty("row", i);
            ellipseWidget->setProperty("column", j);
            
            layout->addWidget(ellipseWidget, i, j);
        }
    }
    

}

void QtWidgetsProject::clearLayout(QLayout* layout)
{
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void QtWidgetsProject::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.eraseRect(rect());
}