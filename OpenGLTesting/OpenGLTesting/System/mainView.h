#ifndef  MAIN_VIEW_H
#define  MAIN_VIEW_H

#include <QGraphicsView.h>
#include <QOpenglWidget.h>

#include <System/mainScene.h>

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
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event);

private:
    MainScene *main_scene_;
    QOpenGLWidget *main_widget_;
};


#endif 