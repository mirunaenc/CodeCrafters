#include "QtWidgetsProject.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QtWidgetsProject w;
    w.show();
    return a.exec();
}

