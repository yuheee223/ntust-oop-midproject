#include "test.h"
#include "ui_test.h"
#include "Reversi.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include < QMessageBox>
#include <QDebug>
#define cout qDebug()

bool test::isSave = false;
bool test::hintStatus = false;

test::test(Reversi* reversiParent, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Form), reversiWindow(reversiParent)
{
    ui->setupUi(this);  
    this->setWindowTitle("Reversi");

    this->setWindowFlags(Qt::FramelessWindowHint);

    start = QPoint(162, 59);
    end = QPoint(494, 375);

    gridW = (end.x() - start.x()) / 8;
    gridH = (end.y() - start.y()) / 8;

    // 新增 SwitchButton
    switchBtn = new SwitchButton(this);
    switchBtn->setFixedWidth(90);
    switchBtn->setTextOn("Hint On");
    switchBtn->setTextOff("Hint Off");
    switchBtn->move(width() - 100, 30); 
    switchBtn->resize(60, 30); 
    switchBtn->show();


    initBoard();

    //connect(ui->exit_btn, &QPushButton::clicked, this, &test::onExitClicked);
    //connect(ui->exit_btn, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->exit_btn, &QPushButton::clicked, this, &test::onExitClicked);
    connect(ui->save_btn, &QPushButton::clicked, this, &test::saveBoardState);

    connect(switchBtn, &SwitchButton::statusChanged, this, &test::onSwitchChanged);

}

void test::onExitClicked() {
    this->hide();  
    reversiWindow->show();  
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

            // 畫出提示位置
            if (hintBoard[i][j] == Hint) {
                // 畫灰色的提示格子，這裡可以選擇使用半透明的灰色
                p.setBrush(QColor(192, 192, 192, 100));  // 半透明灰色
                p.drawRect(start.x() + i * gridW + 1, start.y() + j * gridH + 1, gridW - 2, gridH - 2);  // 畫出提示框
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
            printHintBoard();

            //更新地圖
            update();


            // printboard
            qDebug() << "Board:";
            for (int j = 0; j < 8; j++) { // y-row
                QString row;
                for (int i = 0; i < 8; i++) { // x-col
                    if (board[i][j] == White) {
                        row += "W ";
                    }
                    else if (board[i][j] == Black)
                        row += "B ";
                    else if (board[i][j] == Empty)
                        row += "O ";
                }
                qDebug() << row;
            }
        }
        
    }

}

void test::mouseMoveEvent(QMouseEvent *e) {
    if (e->buttons() & Qt::LeftButton) {
        move(e->globalPosition().toPoint() - p);
    }
}

void test::initBoard() {
    test::isSave = false;

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

    if (switchBtn->checked()) {
        showHintMoves();
    }


    // 檢查新角色是否有合法步驟
    if (!hasValidMove(role)) {
        // 若無合法步驟，則換回原角色
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


    //判斷輸贏
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (judgeRole(i, j, board, Black, false) > 0 || judgeRole(i, j, board, White, false) > 0) {
                return;
            }
        }
    }

    // 遊戲結束
    QString resultMessage;
    // save被更新
    test::isSave = false;

    if (w > b) {
        cout << "white win";
        resultMessage = "White Wins!";
    }
    else if (b > w) {
        cout << "black win";
        resultMessage = "Black Wins!";
    }
    else {
        cout << "score tied";
        resultMessage = "Score Tie!";
    }

    // 顯示結果
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over");
    msgBox.setText(resultMessage);
    msgBox.setIcon(QMessageBox::Information);

    QPushButton* restartButton = msgBox.addButton("Restart", QMessageBox::ActionRole);
    msgBox.addButton(QMessageBox::Close);

    msgBox.exec();

    // 如果按下重新開始，重新初始化遊戲
    if (msgBox.clickedButton() == restartButton) {
        initBoard();  
        showScore();  // 更新分數
        ui->black_label->show(); 
        ui->white_label->hide(); 
    }

}

int test::judgeRole(int x, int y, void* board, boardStatus currentRole, bool eatChess, int gridNum) {
    // 設定 8 個方向
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

    // 2. 設定對手顏色
    boardStatus opponent = (currentRole == Black) ? White : Black;

    // 3. 檢查周圍位置是否可以吃棋
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
                            eatNum++;
                        }
                    }
                    else {
                        tmpX -= dir[i][0]; tmpY -= dir[i][1];
                        while ((tmpX != x) || (tmpY != y)) {
                            tmpX -= dir[i][0]; tmpY -= dir[i][1];
                            eatNum++;
                        }
                    }
                    break;  // 停止這個方向的檢查
                }
                tmpX += dir[i][0]; tmpY += dir[i][1];  // 沒有找到，繼續搜尋
            }
        }
    }

   // cout << "eat: " << eatNum;
    return eatNum;  // 返回吃掉的棋子數量
}


void test::saveBoardState() {
    // 儲存棋盤的當前狀態
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            savedBoard[i][j] = board[i][j];
        }
    }

    savedRole = role;
    hintStatus = switchBtn->checked();
    isSave = true;
    cout << "save";
}

void test::loadBoardState() {
    // 載入已儲存的棋盤狀態
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = savedBoard[i][j];
        }
    }


    switchBtn->setChecked(hintStatus);

    // 讓 Qt 重新繪製棋盤
    update();

    // 設定當前角色 
    role = savedRole;

    // 更新分數
    showScore();

    // 更新label
    if (role == Black) {
        ui->black_label->show();
        ui->white_label->hide();
    }
    else {
        ui->black_label->hide();
        ui->white_label->show();
    }

    cout << "load";
}


bool test::hasValidMove(boardStatus currentRole) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (judgeRole(i, j, board, currentRole, false) > 0) {
                return true;  // 有可行的步驟
            }
        }
    }
    return false;  // 沒有可行的步驟
}

void test::showHintMoves() {
    // 設置所有格子為 Other
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            hintBoard[i][j] = Other;
        }
    }

    // 計算所有可以吃掉對方棋子的格子
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (judgeRole(i, j, board, role, false) > 0) {
                hintBoard[i][j] = Hint;  // 設置為提示格子
            }
        }
    }
}

void test::onSwitchChanged(bool checked) {
    if (checked) {
        showHintMoves();  // 當開啟提示時，計算提示
    }
    else {
        // 當關閉提示時，清空提示
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                hintBoard[i][j] = Other;
            }
        }
    }

    update();  // 更新畫面
}

void test::printHintBoard() {
    qDebug() << "Hint Board:";
    for (int j = 0; j < 8; j++) { // y-row
        QString row;
        for (int i = 0; i < 8; i++) { // x-col
            if (hintBoard[i][j] == Hint) {
                row += "H ";
            }else if (hintBoard[i][j] == Other)
                row += "O ";

        }
        qDebug() << row;
    }
}