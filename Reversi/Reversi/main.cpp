#include "Reversi.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Reversi w;
    w.show();

    return a.exec();
}
