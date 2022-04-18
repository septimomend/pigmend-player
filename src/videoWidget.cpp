/*

GPL-2.0 License
Copyright (c) 2018 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "videoWidget.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QApplication>

#if DEBUG
#include <QDebug>
#endif

#define TIME_TO_HIDE_CURSOR_MS 1000

VideoWidget::VideoWidget(bool isMainScreen, QWidget *parent) : QVideoWidget(parent),
    m_isGlobalWidget(!isMainScreen)
{
    this->setMouseTracking(true);
    m_timer = new QTimer(this);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	m_globalVideoWidget = static_cast<QVideoWidget*>(parent);

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
        this->setFullScreen(false);
        event->accept();
    }
    else
        QVideoWidget::keyPressEvent(event);
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	QVideoWidget *self = m_isGlobalWidget ? this : m_globalVideoWidget;

	if (self->isFullScreen())
	{
		self->setFullScreen(false);
        m_timer->stop();
        QApplication::setOverrideCursor(Qt::ArrowCursor);
        QApplication::changeOverrideCursor(Qt::ArrowCursor);
	}
	else
    {
		self->setFullScreen(true);
        m_timer->start(TIME_TO_HIDE_CURSOR_MS);
    }

    event->accept();
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    QVideoWidget::mousePressEvent(event);
}

void VideoWidget::mouseMoveEvent(QMouseEvent *event)
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    QApplication::changeOverrideCursor(Qt::ArrowCursor);

    if (m_globalVideoWidget->isFullScreen())
        m_timer->start(TIME_TO_HIDE_CURSOR_MS);
    else
        m_timer->stop();

    event->accept();
}

void VideoWidget::manageFullScreen()
{
    if (isFullScreen())
        this->setFullScreen(false);
    else
        this->setFullScreen(true);
}

void VideoWidget::hideCursorOnFullScreen()
{
    QApplication::setOverrideCursor(Qt::BlankCursor);
    QApplication::changeOverrideCursor(Qt::BlankCursor);

    m_timer->stop();
}

void VideoWidget::showCursorOnFullScreen()
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    QApplication::changeOverrideCursor(Qt::ArrowCursor);

    m_timer->stop();
}

void VideoWidget::paintEvent(QPaintEvent *pe)
{
    (void)pe;
    QStyleOption styleOption;
    styleOption.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}
