#ifndef  MAIN_VIEW_H
#define  MAIN_VIEW_H

#include <QGraphicsView.h>

#include "mainScene.h"
#include "TargetWidget.h"

/*
    provide a widget for displaying the contents of mainScene
*/
class MainView : public QGraphicsView
{
    Q_OBJECT

public:
    MainView();
    ~MainView();

    void show_up();

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    MainScene *main_scene_;
    TargetWidget *main_widget_;
};


#endif 