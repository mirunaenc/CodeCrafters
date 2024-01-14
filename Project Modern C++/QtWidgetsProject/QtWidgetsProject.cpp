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
    boardSizeLabel = new QLabel("Board Size:", this);
    layout->addWidget(boardSizeLabel, 2, 0);

    boardSizeSpinBox = new QSpinBox(this);
    layout->addWidget(boardSizeSpinBox, 2, 1);

    pylonsLabel = new QLabel("Pylons per Player:", this);
    layout->addWidget(pylonsLabel, 3, 0);

    pylonsSpinBox = new QSpinBox(this);
    layout->addWidget(pylonsSpinBox, 3, 1);

    bridgesLabel = new QLabel("Bridges per Player:", this);
    layout->addWidget(bridgesLabel, 4, 0);

    bridgesSpinBox = new QSpinBox(this);
    layout->addWidget(bridgesSpinBox, 4, 1);

    QPushButton* newGameButton = new QPushButton("New Game", this);
    connect(newGameButton, &QPushButton::clicked, this, &QtWidgetsProject::newGame);
    layout->addWidget(newGameButton, 5, 0);


}

void QtWidgetsProject::newGame()
{

    uint16_t boardSize = static_cast<uint16_t>(boardSizeSpinBox->value());
    uint16_t nrPylons = static_cast<uint16_t>(pylonsSpinBox->value());
    uint16_t nrBridges = static_cast<uint16_t>(bridgesSpinBox->value());

    delete game;
    game = new twixt::Game(boardSize, nrPylons, nrBridges);

    clearLayout(layout);
    update();
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    for (int i = 0; i < game->getGameBoard().getSize(); i++)
    {
        for (int j = 0; j < game->getGameBoard().getSize(); j++)
        {
            EllipseWidget* ellipseWidget = new EllipseWidget();
            ellipseWidget->setFixedSize(30, 30);
            ellipseWidget->setColor(Qt::white);
            ellipseWidget->setProperty("row", i);
            ellipseWidget->setProperty("column", j);
            connect(ellipseWidget, &EllipseWidget::clicked, this, &QtWidgetsProject::onEllipseClick);
            
            layout->addWidget(ellipseWidget, i, j);
        }
    }
    
    QPushButton* saveButton = new QPushButton("Save");
    connect(saveButton, &QPushButton::clicked, this, &QtWidgetsProject::onSaveClick);
    saveButton->setFixedSize(30 * game->getGameBoard().getSize(), 30);
    layout->addWidget(saveButton, game->getGameBoard().getSize(), 0, 1, game->getGameBoard().getSize(), Qt::AlignHCenter);


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
    drawBridges(painter);
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

    checkWinner();
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

        EllipseWidget* startCircle = qobject_cast<EllipseWidget*>(layout->itemAtPosition(pStart.getLine(), pStart.getColumn()  )->widget());
        EllipseWidget* endCircle = qobject_cast<EllipseWidget*>(layout->itemAtPosition(pEnd.getLine(), pEnd.getColumn()  )->widget());
        QPoint startCenter = startCircle->mapToParent(startCircle->rect().center());
        QPoint endCenter = endCircle->mapToParent(endCircle->rect().center());

        painter.drawLine(startCenter, endCenter);
    }

}

void QtWidgetsProject::checkWinner()
{
    if (game->checkWinCondition())
    {
        QColor winnerColor = (game->getCurrentPlayer()->getColor() == twixt::EColor::RED) ? Qt::red : Qt::black;
        QString winnerMessage = (game->getCurrentPlayer()->getColor() == twixt::EColor::RED) ? "RED player won!" : "BLACK player won!";
        WinnerDialog* winnerDialog = new WinnerDialog(winnerMessage, winnerColor, this);
        winnerDialog->show();
        QCoreApplication::processEvents();
        update();
    }
}

void QtWidgetsProject::onSaveClick()
{
    twixt::GameFileManager::saveGame(*game);
}
