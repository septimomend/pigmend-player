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
	QVideoWidget *self = m_isGlobalWidget ? this : m_globalVideoWidget;

	if (self->isFullScreen())
	{
		// This is magic again
		// see @fullScreenDisabling comment for more info
		self->setFullScreen(false);
		self->setFullScreen(true);
		self->setFullScreen(false);
	}
	else
		self->setFullScreen(true);

	if (self->isFullScreen())
		m_timer->start(TIME_TO_HIDE_CURSOR_MS);
    else
        m_timer->stop();

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
	pe = nullptr;
    QStyleOption styleOption;
    styleOption.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}
