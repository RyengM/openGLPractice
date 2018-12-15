#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OpenGLTesting.h"

class OpenGLTesting : public QMainWindow
{
    Q_OBJECT

public:
    OpenGLTesting(QWidget *parent = Q_NULLPTR);

private:
    Ui::OpenGLTestingClass ui;
};
