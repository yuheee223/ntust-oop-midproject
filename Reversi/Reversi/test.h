#pragma once

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "ui_test.h"
#include "Reversi.h" 

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
    explicit test(Reversi* reversiParent, QWidget* parent = nullptr);  // �ǻ� Reversi ����
    ~test();

    enum boardStatus{Empty, Black, White};

    //��l�ƶ¥մѪ��A
    void initBoard();
    void changeRole();
    void showScore();
    int judgeRole(int x, int y, void *board, boardStatus currentRole, bool eatChess = true, int gridNum = 8);

    void saveBoardState();  
    void loadBoardState();  
    static bool isSave ;
    
    bool hasValidMove(boardStatus currentRole);

protected:
    void paintEvent(QPaintEvent *); //�e�ѽL+�X�l
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *); //move window
    void onExitClicked();

private:
    Ui::Form* ui;
    Reversi* reversiWindow;  // �O�s Reversi ����������
    QPoint p;
    //int role = Black;
    boardStatus role = Black;

    //���W�y��
    QPoint start, end;

    //�C��e��
    int gridW, gridH;
    boardStatus board[8][8];

    boardStatus savedBoard[8][8]; //�����ѽL��m
    boardStatus savedRole;
};
