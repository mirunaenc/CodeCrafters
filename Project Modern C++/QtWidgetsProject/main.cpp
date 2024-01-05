#include "QtWidgetsProject.h"
#include <QtWidgets/QApplication>
#include "board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    twixt::Board board(10);

    QGraphicsView* graphicsView = board.createQGraphicsView(nullptr);

    QtWidgetsProject w;
    w.setCentralWidget(graphicsView);
    w.show();

    return a.exec();
}
