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

void QtWidgetsProject::onEllipseClick()
{
    EllipseWidget* clickedCircle = qobject_cast<EllipseWidget*>(sender());

    int row = clickedCircle->property("row").toInt();
    int col = clickedCircle->property("column").toInt();

    twixt::EColor color = game->getCurrentPlayer()->getColor();

    QColor newColor = (color == twixt::EColor::RED) ? Qt::red : Qt::black;
    try
    {
        game->getCurrentPlayer()->placePylon(row, col);

        clickedCircle->setColor(newColor);
    }
    catch (std::invalid_argument& exception)
    {
        std::cerr << exception.what() << "\n";
    }

    //provizoriu , trebuie sa fac swap la playeri,trebuie inlocuit cu end turn button
    game->swapPlayers();

    update();
}

void QtWidgetsProject::drawBridges(QPainter& painter) 
{
    for (const auto& bridge : game->getGameBoard().getBridges())
    {
        twixt::Pylon pStart = bridge.getStart();
        twixt::Pylon pEnd = bridge.getEnd();

        if (pStart.getColor() == twixt::EColor::RED)
            painter.setPen(QPen(Qt::red, 3, Qt::SolidLine));
        else
            painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));

        CircleWidget* startCircle = qobject_cast<CircleWidget>(layout->itemAtPosition(pStart.getLine(), pStart.getColumn() / pStart.GetPosition().first, pStart.GetPosition().second / )->widget());
        CircleWidget endCircle = qobject_cast<CircleWidget>(layout->itemAtPosition(pEnd.getLine(), pEnd.getColumn() / pEnd.GetPosition().first, pEnd.GetPosition().second * / )->widget());
        QPoint startCenter = startCircle->mapToParent(startCircle->rect().center());
        QPoint endCenter = endCircle->mapToParent(endCircle->rect().center());

        painter.drawLine(startCenter, endCenter);
    }

}