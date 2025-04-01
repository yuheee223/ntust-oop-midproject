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

    //// �Ыذh�X���s
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


    //�e�¥մ�
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            
            if (board[i][j] == Black) {
                //�e�´�
                p.drawPixmap(start.x() + i * gridW, start.y() + j * gridH, gridW - 2, gridH + 6, QPixmap(":/Reversi/black_chess.png"));
            }
            else if (board[i][j] == White) {
                //�e�մ�
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

    //�p����@��Q�I
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

            //��s�a��
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

    //��l�������¥մ�
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

    typedef int(*p)[8];  // ���]�ѽL�j�p�O 8x8
    p chessBoard = p(board);

    // 1. �ˬd�Ӧ�m�O�_����
    if (chessBoard[tmpX][tmpY] != Empty) {
        cout << "not empty";
        return 0;  // �p�G�Ӧ�m�����šA��^ 0
    }

    // 2. �ˬd�P���m�O�_�i�H�Y��
    for (i = 0; i < 8; i++) {
        tmpX = x; tmpY = y;  // ���m tmpX �M tmpY ���_�l��m
        tmpX += dir[i][0]; tmpY += dir[i][1];  // �ھڤ�V����

        if ((tmpX < gridNum && tmpX >= 0 && tmpY < gridNum && tmpY >= 0) &&
            (chessBoard[tmpX][tmpY] != currentRole) && (chessBoard[tmpX][tmpY] != Empty)) {

            tmpX += dir[i][0]; tmpY += dir[i][1];  // �A���ھڤ�V����

            // �i��M���A������Ŧ�Χ��ۤv�Ѥl
            while (tmpX < gridNum && tmpX >= 0 && tmpY < gridNum && tmpY >= 0) {
                if (chessBoard[tmpX][tmpY] == Empty) break;  // �p�G�Ŧ�A�����ˬd
                if (chessBoard[tmpX][tmpY] == currentRole) {
                    // ���ۤv���Ѥl�A�}�l�Y�Ѫ��B�z
                    if (eatChess == true) {
                        chessBoard[x][y] = currentRole;  // ��m�s�Ѥl
                        tmpX -= dir[i][0]; tmpY -= dir[i][1];

                        // �^���æY���Ĥ�Ѥl
                        while ((tmpX != x) || (tmpY != y)) {
                            chessBoard[tmpX][tmpY] = currentRole;  // �Y���Ѥl
                            tmpX -= dir[i][0]; tmpY -= dir[i][1];
                            eatNum++;  // �Y���@���Ѥl
                        }
                    }
                    else {
                        tmpX -= dir[i][0]; tmpY -= dir[i][1];
                        while ((tmpX != x) || (tmpY != y)) {
                            tmpX -= dir[i][0]; tmpY -= dir[i][1];
                            eatNum++;  // �p��Y�����Ѥl�ƶq
                        }
                    }
                    break;  // ����o�Ӥ�V���ˬd
                }
                tmpX += dir[i][0]; tmpY += dir[i][1];  // �S�����A�~��j�M
            }
        }
        // �p�G�o�Ӥ�V����Y�ѡA���s�ˬd�U�@�Ӥ�V
    }

    cout << "eat: " << eatNum;  // ��ܦY�����Ѥl�ƶq
    return eatNum;  // ��^�Y�����Ѥl�ƶq
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
//    // ��s���A����
//    statusLabel->setText((context.GetCurrentState() == test::GAME_STATE::BLACK_TURN) ? "����¤l" : "����դl");
//}

void test::onCellClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    // ��X���s�y��
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

    //// ���դU��
    //Reversi::PLAYER_COLOR currentPlayer =
    //    (context.GetCurrentState() == Reversi::GAME_STATE::BLACK_TURN) ?
    //    Reversi::PLAYER_COLOR::BLACK : Reversi::PLAYER_COLOR::WHITE;

    //if (context.IsValidMove(row, col, currentPlayer)) {
    //    context.SetSlotStatus(row, col, (currentPlayer == Reversi::PLAYER_COLOR::BLACK) ?
    //        Reversi::SLOT_STATUS::BLACK : Reversi::SLOT_STATUS::WHITE);
    //    context.FlipDisks(row, col);

    //    // �������a
    //    context.SetCurrentState((currentPlayer == Reversi::PLAYER_COLOR::BLACK) ?
    //        Reversi::GAME_STATE::WHITE_TURN :
    //        Reversi::GAME_STATE::BLACK_TURN);
    //}

    // updateBoard();
   // statusLabel = new QLabel("yessss!", this);
}

