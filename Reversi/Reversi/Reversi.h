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

protected:
    void showEvent(QShowEvent* event) override;

private:
    Ui::ReversiClass ui;
};
