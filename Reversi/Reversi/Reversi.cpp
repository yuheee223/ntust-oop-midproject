#include "Reversi.h"
#include "test.h"
#include <iostream>

Reversi::Reversi(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("Reversi");
    test *test_test = new test;

    connect(ui.game_start_btn, SIGNAL(clicked(bool)), this, SLOT(hide()));
    connect(ui.game_start_btn, SIGNAL(clicked(bool)), test_test, SLOT(show()));
  //  connect(ui->startButton, &QPushButton::clicked, this, &Reversi::startGame);

}

Reversi::~Reversi()
{}

//void Reversi::startGame()
//{
//    gameWindow = new test(this);
//    gameWindow->show();
//    this->hide();  // ÁôÂÃ¥Dµøµ¡
//}
