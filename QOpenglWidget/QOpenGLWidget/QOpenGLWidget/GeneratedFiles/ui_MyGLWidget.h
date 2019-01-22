/********************************************************************************
** Form generated from reading UI file 'MyGLWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYGLWIDGET_H
#define UI_MYGLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyGLWidgetClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyGLWidgetClass)
    {
        if (MyGLWidgetClass->objectName().isEmpty())
            MyGLWidgetClass->setObjectName(QStringLiteral("MyGLWidgetClass"));
        MyGLWidgetClass->resize(600, 400);
        menuBar = new QMenuBar(MyGLWidgetClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MyGLWidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyGLWidgetClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyGLWidgetClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MyGLWidgetClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MyGLWidgetClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyGLWidgetClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyGLWidgetClass->setStatusBar(statusBar);

        retranslateUi(MyGLWidgetClass);

        QMetaObject::connectSlotsByName(MyGLWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyGLWidgetClass)
    {
        MyGLWidgetClass->setWindowTitle(QApplication::translate("MyGLWidgetClass", "MyGLWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyGLWidgetClass: public Ui_MyGLWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYGLWIDGET_H
