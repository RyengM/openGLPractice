#include <QScreen.h>
#include <QtGui/QEvent.h>
#include <qguiapplication.h>

#include "mainView.h"

MainView::MainView()
{
    setWindowTitle(QStringLiteral("部件测试平台"));
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    //main widget for loading OPENGL items
    main_widget_ = new QGLWidget(QGLFormat(QGL::SampleBuffers));
    main_widget_->makeCurrent();
    setViewport(main_widget_);
    //viewport will never be updated when secene is changed, user is expected to controll all updates
    setViewportUpdateMode(NoViewportUpdate);

    main_scene_ = new MainScene(main_widget_);
    setScene(main_scene_);
    setContentsMargins(0, 0, 0, 0);
}

MainView::~MainView()
{
    delete main_scene_;
    delete main_widget_;
}

void MainView::show_up()
{
#ifdef _WIN32
    showFullScreen();
#else
    showMaximized();
#endif
}

void MainView::closeEvent(QCloseEvent* event)
{
}

void MainView::resizeEvent(QResizeEvent* event)
{
    if (scene())
    {
#ifndef _WIN32
        QSize screen_size = QGuiApplication::primaryScreen()->availableSize();
        scene()->setSceneRect(QRect(QPoint(0, 0), screen_size - QSize(2, 2)));
        if (screen_size - QSize(2, 2) == event->size())
            main_scene_->initialize();
#else
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        QSize screen_size = QGuiApplication::primaryScreen()->size();
        if (screen_size - QSize(2, 2) == event->size())
            main_scene_->initialize();
#endif
    }

    QGraphicsView::resizeEvent(event);
}

void MainView::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
}