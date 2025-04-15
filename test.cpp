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

    // �s�W SwitchButton
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

            // �e�X���ܦ�m
            if (hintBoard[i][j] == Hint) {
                // �e�Ǧ⪺���ܮ�l�A�o�̥i�H��ܨϥΥb�z�����Ǧ�
                p.setBrush(QColor(192, 192, 192, 100));  // �b�z���Ǧ�
                p.drawRect(start.x() + i * gridW + 1, start.y() + j * gridH + 1, gridW - 2, gridH - 2);  // �e�X���ܮ�
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
            printHintBoard();

            //��s�a��
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

    if (switchBtn->checked()) {
        showHintMoves();
    }


    // �ˬd�s����O�_���X�k�B�J
    if (!hasValidMove(role)) {
        // �Y�L�X�k�B�J�A�h���^�쨤��
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


    //�P�_��Ĺ
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (judgeRole(i, j, board, Black, false) > 0 || judgeRole(i, j, board, White, false) > 0) {
                return;
            }
        }
    }

    // �C������
    QString resultMessage;
    // save�Q��s
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

    // ��ܵ��G
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over");
    msgBox.setText(resultMessage);
    msgBox.setIcon(QMessageBox::Information);

    QPushButton* restartButton = msgBox.addButton("Restart", QMessageBox::ActionRole);
    msgBox.addButton(QMessageBox::Close);

    msgBox.exec();

    // �p�G���U���s�}�l�A���s��l�ƹC��
    if (msgBox.clickedButton() == restartButton) {
        initBoard();  
        showScore();  // ��s����
        ui->black_label->show(); 
        ui->white_label->hide(); 
    }

}

int test::judgeRole(int x, int y, void* board, boardStatus currentRole, bool eatChess, int gridNum) {
    // �]�w 8 �Ӥ�V
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

    // 2. �]�w����C��
    boardStatus opponent = (currentRole == Black) ? White : Black;

    // 3. �ˬd�P���m�O�_�i�H�Y��
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
                    break;  // ����o�Ӥ�V���ˬd
                }
                tmpX += dir[i][0]; tmpY += dir[i][1];  // �S�����A�~��j�M
            }
        }
    }

   // cout << "eat: " << eatNum;
    return eatNum;  // ��^�Y�����Ѥl�ƶq
}


void test::saveBoardState() {
    // �x�s�ѽL����e���A
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
    // ���J�w�x�s���ѽL���A
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = savedBoard[i][j];
        }
    }


    switchBtn->setChecked(hintStatus);

    // �� Qt ���sø�s�ѽL
    update();

    // �]�w��e���� 
    role = savedRole;

    // ��s����
    showScore();

    // ��slabel
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
                return true;  // ���i�檺�B�J
            }
        }
    }
    return false;  // �S���i�檺�B�J
}

void test::showHintMoves() {
    // �]�m�Ҧ���l�� Other
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            hintBoard[i][j] = Other;
        }
    }

    // �p��Ҧ��i�H�Y�����Ѥl����l
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (judgeRole(i, j, board, role, false) > 0) {
                hintBoard[i][j] = Hint;  // �]�m�����ܮ�l
            }
        }
    }
}

void test::onSwitchChanged(bool checked) {
    if (checked) {
        showHintMoves();  // ��}�Ҵ��ܮɡA�p�ⴣ��
    }
    else {
        // ���������ܮɡA�M�Ŵ���
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                hintBoard[i][j] = Other;
            }
        }
    }

    update();  // ��s�e��
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