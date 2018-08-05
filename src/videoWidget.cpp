/*
MIT License

Copyright (c) 2018 Ivan Chapkailo

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "videoWidget.h"

#include <QKeyEvent>
#include <QMouseEvent>

#define TIME_TO_HIDE_CURSOR_MS 1000

VideoWidget::VideoWidget(bool isMainScreen, QWidget *parent) : QVideoWidget(parent),
    m_isGlobalWidget(!isMainScreen)
{
    this->setMouseTracking(true);
    m_timer = new QTimer(this);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_globalVideoWidget = (QVideoWidget *)parent;

    if (isMainScreen)
        setStyleSheet("image: url(:/custom/img/custom/pigmendback.png)");

    connect(m_timer, SIGNAL(timeout()), this, SLOT(hideCursorOnFullScreen()));
}

VideoWidget::~VideoWidget()
{
    delete m_timer;
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && isFullScreen())
    {
        // @fullScreenDiasbling
        // This is some magic
        // If do that the turning from full screen mode to normal is fine
        // but if use only
        // this->setFullScreen(false);
        // the video widget will be detached and video will not be shown
        this->setFullScreen(false);
        this->setFullScreen(true);
        this->setFullScreen(false);
        event->accept();
    }
    else if (event->key() == Qt::Key_Enter && event->modifiers() & Qt::Key_Alt)
    {
        this->setFullScreen(!isFullScreen());
        event->accept();
    }
    else
        QVideoWidget::keyPressEvent(event);
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (m_globalVideoWidget->isFullScreen())
    {
        // This is magic again
        // see @fullScreenDisabling comment for more info
        m_globalVideoWidget->setFullScreen(false);
        m_globalVideoWidget->setFullScreen(true);
        m_globalVideoWidget->setFullScreen(false);
    }
    else
        m_globalVideoWidget->setFullScreen(true);

    if (m_globalVideoWidget->isFullScreen())
        m_timer->start(TIME_TO_HIDE_CURSOR_MS);

    event->accept();
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    QVideoWidget::mousePressEvent(event);
}

void VideoWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->setCursor(Qt::CustomCursor);

    if (m_globalVideoWidget->isFullScreen())
        m_timer->start(TIME_TO_HIDE_CURSOR_MS);

    event->accept();
}

void VideoWidget::enableFullScreen()
{
    if (isFullScreen())
    {
        // @fullScreenDiasbling
        this->setFullScreen(false);
        this->setFullScreen(true);
        this->setFullScreen(false);
    }
    else
        this->setFullScreen(true);
}

void VideoWidget::hideCursorOnFullScreen()
{
    this->setCursor(Qt::BlankCursor);
}

void VideoWidget::paintEvent(QPaintEvent *pe)
{
    pe = pe;
    QStyleOption styleOption;
    styleOption.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}
