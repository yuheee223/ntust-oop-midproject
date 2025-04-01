#include "Reversi.h"
#include <QtWidgets/QApplication>
//#include "ReversiGame.h"
//#include "ReversiContext.h"
//#include "ReversiInput.cpp"
//#include "ReversiView.cpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Reversi w;
    w.show();

    //Reversi::ReversiContext context;
    //Reversi::ReversiInput input;
    //Reversi::ReversiView view;

    //Reversi::ReversiGame game(&context, &input, &view);

    //game.Execute();
    return a.exec();
}
