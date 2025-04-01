#pragma once

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "ui_test.h"
//#include "ReversiContext.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Form; } 
QT_END_NAMESPACE

//namespace Ui {
//    class test;
//}

class test : public QMainWindow
{
    Q_OBJECT

public:
    test(QWidget* parent = nullptr);
    ~test();

    enum boardStatus{Empty, Black, White};

    //��l�ƶ¥մѪ��A
    void initBoard();
    void changeRole();
    void showScore();
    int judgeRole(int x, int y, void *board, boardStatus currentRole, bool eatChess = true, int gridNum = 8);

private slots:
   void onCellClicked();  // �B�z�I���ƥ�
  // void updateBoard();    // ��s�ѽL���

protected:
    void paintEvent(QPaintEvent *); //�e�ѽL+�X�l
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *); //move window

private:
    Ui::Form* ui;
    QPoint p;
    //int role = Black;
    boardStatus role = Black;

    //���W�y��
    QPoint start, end;

    //�C��e��
    int gridW, gridH;
    int board[8][8];

    QGridLayout* gridLayout;
    QPushButton* cells[8][8];  // 8x8 �ѽL
    QLabel* statusLabel;
    // Reversi::ReversiContext context;
};
