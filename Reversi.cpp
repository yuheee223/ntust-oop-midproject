#include "Reversi.h"
#include "test.h"
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QShowEvent>

#define cout qDebug()

Reversi::Reversi(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("Reversi");
    test *test_test = new test(this);


    connect(ui.game_start_btn, SIGNAL(clicked(bool)), this, SLOT(hide()));
    connect(ui.game_start_btn, SIGNAL(clicked(bool)), test_test, SLOT(show()));


    connect(ui.game_start_btn, &QPushButton::clicked, [test_test]() {
        if (test_test->isSave) {  
            test_test->loadBoardState();  // 載入儲存的棋盤
            test_test->onSwitchChanged(test_test->hintStatus);
        }
        else {
            test_test->initBoard();  // 初始化新的棋盤
            test_test->switchBtn->setChecked(false);
            test_test->onSwitchChanged(false);
        }
        });

}

Reversi::~Reversi()
{}

void Reversi::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);  // 確保父類的 `showEvent` 也被執行

    cout << "save: " << test::isSave;
    if (test::isSave) {
        ui.game_start_btn->setText("Continue");
    }
    else {
        ui.game_start_btn->setText("Game Start!");
    }
}

