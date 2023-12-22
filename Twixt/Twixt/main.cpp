#include "Twixt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Twixt w;
    w.show();
    return a.exec();
}
