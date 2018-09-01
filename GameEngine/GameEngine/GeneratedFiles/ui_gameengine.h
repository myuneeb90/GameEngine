/********************************************************************************
** Form generated from reading UI file 'gameengine.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEENGINE_H
#define UI_GAMEENGINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameEngineClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GameEngineClass)
    {
        if (GameEngineClass->objectName().isEmpty())
            GameEngineClass->setObjectName(QStringLiteral("GameEngineClass"));
        GameEngineClass->resize(1024, 800);
        centralWidget = new QWidget(GameEngineClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GameEngineClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameEngineClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        GameEngineClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GameEngineClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GameEngineClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GameEngineClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GameEngineClass->setStatusBar(statusBar);

        retranslateUi(GameEngineClass);

        QMetaObject::connectSlotsByName(GameEngineClass);
    } // setupUi

    void retranslateUi(QMainWindow *GameEngineClass)
    {
        GameEngineClass->setWindowTitle(QApplication::translate("GameEngineClass", "GameEngine", 0));
    } // retranslateUi

};

namespace Ui {
    class GameEngineClass: public Ui_GameEngineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEENGINE_H
