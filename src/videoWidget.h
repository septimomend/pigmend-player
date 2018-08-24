/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>
#include <QStyleOption>
#include <QPainter>
#include <QTimer>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    VideoWidget(bool isMainScreen = false, QWidget *parent = 0);
    ~VideoWidget();

public slots:
    void manageFullScreen();    // sets full screen after fullScreenButton is clicked

private slots:
    void hideCursorOnFullScreen();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *pe) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    bool m_isGlobalWidget;
    QVideoWidget *m_globalVideoWidget;
    QTimer *m_timer;
};

#endif // VIDEOWIDGET_H
