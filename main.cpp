#include <QApplication>
#include "BitCalc.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    BitCalc mainWindow;
    mainWindow.show();

    return app.exec();

}

