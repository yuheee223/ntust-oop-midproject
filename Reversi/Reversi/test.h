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

    //初始化黑白棋狀態
    void initBoard();
    void changeRole();
    void showScore();
    int judgeRole(int x, int y, void *board, boardStatus currentRole, bool eatChess = true, int gridNum = 8);

private slots:
   void onCellClicked();  // 處理點擊事件
  // void updateBoard();    // 更新棋盤顯示

protected:
    void paintEvent(QPaintEvent *); //畫棋盤+旗子
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *); //move window

private:
    Ui::Form* ui;
    QPoint p;
    //int role = Black;
    boardStatus role = Black;

    //左上座標
    QPoint start, end;

    //每格寬高
    int gridW, gridH;
    int board[8][8];

    QGridLayout* gridLayout;
    QPushButton* cells[8][8];  // 8x8 棋盤
    QLabel* statusLabel;
    // Reversi::ReversiContext context;
};
