/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLCDNumber *black_num;
    QPushButton *save_btn;
    QPushButton *exit_btn;
    QLCDNumber *white_num;
    QLabel *black_label;
    QLabel *white_label;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(678, 460);
        black_num = new QLCDNumber(Form);
        black_num->setObjectName("black_num");
        black_num->setGeometry(QRect(20, 160, 81, 41));
        black_num->setFrameShape(QFrame::Shape::NoFrame);
        black_num->setDigitCount(2);
        save_btn = new QPushButton(Form);
        save_btn->setObjectName("save_btn");
        save_btn->setGeometry(QRect(220, 410, 80, 29));
        QFont font;
        font.setFamilies({QString::fromUtf8("Lucida Console")});
        font.setPointSize(16);
        save_btn->setFont(font);
        exit_btn = new QPushButton(Form);
        exit_btn->setObjectName("exit_btn");
        exit_btn->setGeometry(QRect(350, 410, 80, 29));
        exit_btn->setFont(font);
        white_num = new QLCDNumber(Form);
        white_num->setObjectName("white_num");
        white_num->setGeometry(QRect(570, 160, 81, 41));
        white_num->setFrameShape(QFrame::Shape::NoFrame);
        white_num->setDigitCount(2);
        black_label = new QLabel(Form);
        black_label->setObjectName("black_label");
        black_label->setGeometry(QRect(50, 110, 41, 41));
        black_label->setPixmap(QPixmap(QString::fromUtf8("black.png")));
        black_label->setScaledContents(true);
        white_label = new QLabel(Form);
        white_label->setObjectName("white_label");
        white_label->setGeometry(QRect(600, 110, 41, 41));
        white_label->setPixmap(QPixmap(QString::fromUtf8("white.png")));
        white_label->setScaledContents(true);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Reversi", nullptr));
        save_btn->setText(QCoreApplication::translate("Form", "save", nullptr));
        exit_btn->setText(QCoreApplication::translate("Form", "exit", nullptr));
        black_label->setText(QString());
        white_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
