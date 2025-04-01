#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Reversi.h"
#include "test.h"

class Reversi : public QMainWindow
{
    Q_OBJECT

public:
    Reversi(QWidget *parent = nullptr);
    ~Reversi();

//public slots:
//    void startGame();

private:
    Ui::ReversiClass ui;
};
