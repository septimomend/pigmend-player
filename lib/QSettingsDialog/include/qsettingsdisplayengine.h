#ifndef QSETTINGSDISPLAYENGINE_H
#define QSETTINGSDISPLAYENGINE_H

#include "qsettingsdialog_global.h"
class QWindow;
struct SettingsRoot;

//! @intuse An interface for a display instance that can be controlled by the dialog @ingroup grp_core
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDisplayInstance
{
public:
	//! Virtual destructor
	inline virtual ~QSettingsDisplayInstance() {}

	//! Sets the parent window of this instance
	virtual void setParentWindow(QWidget *parent) = 0;
	//! Sets the parent window of this instance
	virtual void setParentWindow(QWindow *parent) = 0;
	//! Passes the current settings structure, to create the ui
	virtual void createUi(const QSharedPointer<SettingsRoot> &rootElement) = 0;

public slots:
	//! Opens the dialog non blocking
	virtual void open() = 0;
	//! Opens the dialog blocking, waiting for a result
	virtual int exec() = 0;

signals:
	//! Should be emitted everytime settings are saved
	virtual void saved(bool closed) = 0;
	//! Should be emitted when settings have been resetted and the dialog closed
	virtual void resetted() = 0;
	//! Should be emitted when the dialog was canceled
	virtual void canceled() = 0;
};

//! @intuse An interface for an engine to create display dialogs @ingroup grp_core
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDisplayEngine
{
public:
	//! Virtual destructor
	inline virtual ~QSettingsDisplayEngine() {}

	//! Creates a new display instance
	virtual QSettingsDisplayInstance *createInstance() = 0;
};

#endif // QSETTINGSDISPLAYENGINE_H
