#pragma once

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "ui_test.h"
#include "Reversi.h" 
#include "SwitchButton.h" 

QT_BEGIN_NAMESPACE
namespace Ui { class Form; } 
QT_END_NAMESPACE

//namespace Ui {
//    class test;
//}
class Reversi;

class test : public QMainWindow
{
    Q_OBJECT

public:
    //test(QWidget* parent = nullptr);
    explicit test(Reversi* reversiParent, QWidget* parent = nullptr);  // 傳遞 Reversi 視窗
    ~test();

    enum boardStatus{Empty, Black, White};
    enum HintStatus {
        Other = 0,
        Hint = 1 
    };


    //初始化黑白棋狀態
    void initBoard();
    void changeRole();
    void showScore();
    int judgeRole(int x, int y, void *board, boardStatus currentRole, bool eatChess = true, int gridNum = 8);

    void saveBoardState();  
    void loadBoardState();  
    static bool isSave ;
    
    bool hasValidMove(boardStatus currentRole);

    void showHintMoves();
    void printHintBoard();

protected:
    void paintEvent(QPaintEvent *); //畫棋盤+旗子
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *); //move window
    void onExitClicked();
    void onSwitchChanged(bool checked);

private:
    Ui::Form* ui;
    Reversi* reversiWindow;  // 保存 Reversi 視窗的指標
    QPoint p;
    //int role = Black;
    boardStatus role = Black;

    //左上座標
    QPoint start, end;

    //每格寬高
    int gridW, gridH;
    boardStatus board[8][8];

    boardStatus savedBoard[8][8]; //紀錄棋盤位置
    boardStatus savedRole;

    SwitchButton* switchBtn;
    HintStatus hintBoard[8][8];
};
