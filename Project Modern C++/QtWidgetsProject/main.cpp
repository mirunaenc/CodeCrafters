#include "QtWidgetsProject.h"
#include <QtWidgets/QApplication>
#include "pylon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsProject w;
    w.show();

   twixt::Pylon pylon(2 , 2);
   pylon.setColor(twixt::EColor::RED);


    return a.exec();
}
