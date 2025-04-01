/********************************************************************************
** Form generated from reading UI file 'Reversi.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVERSI_H
#define UI_REVERSI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReversiClass
{
public:
    QWidget *centralWidget;
    QPushButton *game_start_btn;
    QLabel *Initial_label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ReversiClass)
    {
        if (ReversiClass->objectName().isEmpty())
            ReversiClass->setObjectName("ReversiClass");
        ReversiClass->resize(600, 400);
        centralWidget = new QWidget(ReversiClass);
        centralWidget->setObjectName("centralWidget");
        game_start_btn = new QPushButton(centralWidget);
        game_start_btn->setObjectName("game_start_btn");
        game_start_btn->setGeometry(QRect(210, 270, 141, 39));
        QFont font;
        font.setFamilies({QString::fromUtf8("Maiandra GD")});
        font.setPointSize(18);
        font.setItalic(false);
        game_start_btn->setFont(font);
        Initial_label = new QLabel(centralWidget);
        Initial_label->setObjectName("Initial_label");
        Initial_label->setGeometry(QRect(180, 190, 212, 48));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Lucida Console")});
        font1.setPointSize(36);
        font1.setBold(true);
        font1.setItalic(true);
        Initial_label->setFont(font1);
        ReversiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ReversiClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        ReversiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ReversiClass);
        mainToolBar->setObjectName("mainToolBar");
        ReversiClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ReversiClass);
        statusBar->setObjectName("statusBar");
        ReversiClass->setStatusBar(statusBar);

        retranslateUi(ReversiClass);

        QMetaObject::connectSlotsByName(ReversiClass);
    } // setupUi

    void retranslateUi(QMainWindow *ReversiClass)
    {
        ReversiClass->setWindowTitle(QCoreApplication::translate("ReversiClass", "Reversi", nullptr));
        game_start_btn->setText(QCoreApplication::translate("ReversiClass", "Game Start!", nullptr));
        Initial_label->setText(QCoreApplication::translate("ReversiClass", "Reversi", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReversiClass: public Ui_ReversiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVERSI_H
