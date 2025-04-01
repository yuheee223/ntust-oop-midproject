#include "test.h"
#include "ui_test.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#define cout qDebug()


test::test(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Form)  
{
    ui->setupUi(this);  
    this->setWindowTitle("Reversi");

    this->setWindowFlags(Qt::FramelessWindowHint);

    start = QPoint(162, 59);
    end = QPoint(494, 375);

    gridW = (end.x() - start.x()) / 8;
    gridH = (end.y() - start.y()) / 8;

    initBoard();


    //reversi* Reversi = new Reversi;

    //QWidget* centralWidget = new QWidget(this);
    //setCentralWidget(centralWidget);

    //gridLayout = new QGridLayout(centralWidget);

    //for (int i = 0; i < 8; ++i) {
    //    for (int j = 0; j < 8; ++j) {
    //        cells[i][j] = new QPushButton(this);
    //        cells[i][j]->setFixedSize(50, 50);
    //        gridLayout->addWidget(cells[i][j], i, j);
    //        connect(cells[i][j], &QPushButton::clicked, this, &test::onCellClicked);
    //    }
    //}
    //gridLayout->addWidget(statusLabel, 8, 0, 1, 8);

    //// 創建退出按鈕
    //QPushButton* exit_btn = new QPushButton("EXIT", this);
    //exit_btn->setObjectName("exit_btn");
    //exit_btn->setGeometry(QRect(170, 320, 80, 25));

    //QFont font;
    //font.setFamilies({ QString::fromUtf8("Lucida Console") });
    //font.setPointSize(10);
    //exit_btn->setFont(font);

    //gridLayout->addWidget(exit_btn, 9, 0, 1, 8);   
    
    connect(ui->exit_btn, &QPushButton::clicked, this, &QWidget::close);

}

test::~test()
{
    delete ui; 
}

void test::paintEvent(QPaintEvent*) {
    QPainter p(this);

    // background
    p.drawPixmap(this->rect(), QPixmap("://Reversi/chess-board.png"));


    //畫黑白棋
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            
            if (board[i][j] == Black) {
                //畫黑棋
                p.drawPixmap(start.x() + i * gridW, start.y() + j * gridH, gridW - 2, gridH + 6, QPixmap(":/Reversi/black_chess.png"));
            }
            else if (board[i][j] == White) {
                //畫白棋
                p.drawPixmap(start.x() + i * gridW, start.y() + j * gridH, gridW - 2, gridH + 6, QPixmap(":/Reversi/white_chess.png"));

            }
        }
    }
}

void test::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::LeftButton) {
        p = e->globalPosition().toPoint() - this->frameGeometry().topLeft();
    }

    cout << e->pos();

    //計算哪一格被點
    int x = e->position().x();
    int y = e->position().y();
    int i = 0;
    int j = 0;

    if (x >= start.x() && x <= (start.x() + 8 * gridW) && y >= start.y() && y <= (start.y() + 8 * gridH)) {
        i = (e->position().x() - start.x()) / gridW;
        j = (e->position().y() - start.y()) / gridH;
        cout << "row = " << i << ",colum = " << j;

        //board[i][j] = role;
        //boardStatus currentrole = static_cast<boardStatus>(role);

        if (judgeRole(i ,j, board, role) > 0) {
            this->changeRole();

            //更新地圖
            update();
        }
        


    }

}

void test::mouseMoveEvent(QMouseEvent *e) {
    if (e->buttons() & Qt::LeftButton) {
        move(e->globalPosition().toPoint() - p);
    }
}

void test::initBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = Empty;
        }
    }

    //初始中間的黑白棋
    board[3][3] = Black;
    board[4][3] = White;
    board[3][4] = White;
    board[4][4] = Black;

    ui->black_label->show();
    ui->white_label->hide();

    ui->black_num->display(2);
    ui->white_num->display(2);
}

void test::changeRole() {
    if (role == Black) {
        role = White;
        ui->black_label->hide();
        ui->white_label->show();
    }
    else {
        role = Black;
        ui->black_label->show();
        ui->white_label->hide();
    }

    showScore();
}

void test::showScore() {
    int b = 0;
    int w = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == Black) {
                b++;
            }
            else if (board[i][j] == White) {
                w++;
            }
        }
    }

    ui->black_num->display(b);
    ui->white_num->display(w);
}

int test::judgeRole(int x, int y, void* board, boardStatus currentRole, bool eatChess, int gridNum) {
    int dir[8][2] = { {1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1} };
    int tmpX = x, tmpY = y;
    int i = 0, eatNum = 0;

    typedef int(*p)[8];  // 假設棋盤大小是 8x8
    p chessBoard = p(board);

    // 1. 檢查該位置是否為空
    if (chessBoard[tmpX][tmpY] != Empty) {
        cout << "not empty";
        return 0;  // 如果該位置不為空，返回 0
    }

    // 2. 檢查周圍位置是否可以吃棋
    for (i = 0; i < 8; i++) {
        tmpX = x; tmpY = y;  // 重置 tmpX 和 tmpY 為起始位置
        tmpX += dir[i][0]; tmpY += dir[i][1];  // 根據方向移動

        if ((tmpX < gridNum && tmpX >= 0 && tmpY < gridNum && tmpY >= 0) &&
            (chessBoard[tmpX][tmpY] != currentRole) && (chessBoard[tmpX][tmpY] != Empty)) {

            tmpX += dir[i][0]; tmpY += dir[i][1];  // 再次根據方向移動

            // 進行遍歷，直到找到空位或找到自己棋子
            while (tmpX < gridNum && tmpX >= 0 && tmpY < gridNum && tmpY >= 0) {
                if (chessBoard[tmpX][tmpY] == Empty) break;  // 如果空位，停止檢查
                if (chessBoard[tmpX][tmpY] == currentRole) {
                    // 找到自己的棋子，開始吃棋的處理
                    if (eatChess == true) {
                        chessBoard[x][y] = currentRole;  // 放置新棋子
                        tmpX -= dir[i][0]; tmpY -= dir[i][1];

                        // 回溯並吃掉敵方棋子
                        while ((tmpX != x) || (tmpY != y)) {
                            chessBoard[tmpX][tmpY] = currentRole;  // 吃掉棋子
                            tmpX -= dir[i][0]; tmpY -= dir[i][1];
                            eatNum++;  // 吃掉一顆棋子
                        }
                    }
                    else {
                        tmpX -= dir[i][0]; tmpY -= dir[i][1];
                        while ((tmpX != x) || (tmpY != y)) {
                            tmpX -= dir[i][0]; tmpY -= dir[i][1];
                            eatNum++;  // 計算吃掉的棋子數量
                        }
                    }
                    break;  // 停止這個方向的檢查
                }
                tmpX += dir[i][0]; tmpY += dir[i][1];  // 沒有找到，繼續搜尋
            }
        }
        // 如果這個方向不能吃棋，重新檢查下一個方向
    }

    cout << "eat: " << eatNum;  // 顯示吃掉的棋子數量
    return eatNum;  // 返回吃掉的棋子數量
}



//void test::updateBoard()
//{
//    for (int i = 0; i < 8; ++i) {
//        for (int j = 0; j < 8; ++j) {
//            switch (context.GetSlotStatus(i, j)) {
//            case test::SLOT_STATUS::EMPTY:
//                cells[i][j]->setText("");
//                break;
//            case test::SLOT_STATUS::BLACK:
//                cells[i][j]->setText("B");
//                break;
//            case test::SLOT_STATUS::WHITE:
//                cells[i][j]->setText("W");
//                break;
//            }
//        }
//    }
//
//    // 更新狀態標籤
//    statusLabel->setText((context.GetCurrentState() == test::GAME_STATE::BLACK_TURN) ? "輪到黑子" : "輪到白子");
//}

void test::onCellClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    // 找出按鈕座標
    int row, col;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (cells[i][j] == btn) {
                row = i;
                col = j;
                break;
            }
        }
    }

    //// 嘗試下棋
    //Reversi::PLAYER_COLOR currentPlayer =
    //    (context.GetCurrentState() == Reversi::GAME_STATE::BLACK_TURN) ?
    //    Reversi::PLAYER_COLOR::BLACK : Reversi::PLAYER_COLOR::WHITE;

    //if (context.IsValidMove(row, col, currentPlayer)) {
    //    context.SetSlotStatus(row, col, (currentPlayer == Reversi::PLAYER_COLOR::BLACK) ?
    //        Reversi::SLOT_STATUS::BLACK : Reversi::SLOT_STATUS::WHITE);
    //    context.FlipDisks(row, col);

    //    // 切換玩家
    //    context.SetCurrentState((currentPlayer == Reversi::PLAYER_COLOR::BLACK) ?
    //        Reversi::GAME_STATE::WHITE_TURN :
    //        Reversi::GAME_STATE::BLACK_TURN);
    //}

    // updateBoard();
   // statusLabel = new QLabel("yessss!", this);
}

