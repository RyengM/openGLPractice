/********************************************************************************
** Form generated from reading UI file 'OpenGLTesting.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENGLTESTING_H
#define UI_OPENGLTESTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenGLTestingClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OpenGLTestingClass)
    {
        if (OpenGLTestingClass->objectName().isEmpty())
            OpenGLTestingClass->setObjectName(QStringLiteral("OpenGLTestingClass"));
        OpenGLTestingClass->resize(600, 400);
        menuBar = new QMenuBar(OpenGLTestingClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        OpenGLTestingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OpenGLTestingClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OpenGLTestingClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(OpenGLTestingClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        OpenGLTestingClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OpenGLTestingClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OpenGLTestingClass->setStatusBar(statusBar);

        retranslateUi(OpenGLTestingClass);

        QMetaObject::connectSlotsByName(OpenGLTestingClass);
    } // setupUi

    void retranslateUi(QMainWindow *OpenGLTestingClass)
    {
        OpenGLTestingClass->setWindowTitle(QApplication::translate("OpenGLTestingClass", "OpenGLTesting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpenGLTestingClass: public Ui_OpenGLTestingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGLTESTING_H
