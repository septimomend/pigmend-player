#ifndef QSETTINGSLOADER_H
#define QSETTINGSLOADER_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QVariant>

class QSimpleSettingsLoader;
class QAsyncSettingsLoader;
/*!
 * @addtogroup grp_core
 * @{
 */

//! The basic settings loader class. Serves as utility class
class QSETTINGSDIALOGSHARED_EXPORT QSettingsLoader
{
	friend class QSimpleSettingsLoader;
	friend class QAsyncSettingsLoader;
	Q_DISABLE_COPY(QSettingsLoader)

public:
	//! Virtual destructor
	virtual inline ~QSettingsLoader() {}
	//! Specifies, whether this loader is async or not
	virtual bool isAsync() const = 0;

	//! Casts this instance to a QSimpleSettingsLoader. Will assert if the conversion fails
	QSimpleSettingsLoader *simple();
	//! Casts this instance to a QAsyncSettingsLoader. Will assert if the conversion fails
	QAsyncSettingsLoader *async();

private:
	//! Private constructor to prevent implementation from other classes
	QSettingsLoader();
};

//! Defines a simple, synchronous loader
class QSETTINGSDIALOGSHARED_EXPORT QSimpleSettingsLoader : public QSettingsLoader
{
public:
	bool isAsync() const final;

	//! Will be called if settings need to be loaded form this loader
	virtual bool load(QVariant outParam data, bool outParam userEdited) = 0;
	//! Will be called to save settings from the dialog to this loader
	virtual bool save(const QVariant &data) = 0;
	//! Will be called to reset the data this loader manages
	virtual bool reset() = 0;
};

//! Defines an asynchronous loader, that can load settings from any thread with any delay
class QSETTINGSDIALOGSHARED_EXPORT QAsyncSettingsLoader : public QObject, public QSettingsLoader
{
	Q_OBJECT

public:
	//! Constructs a new loader (without a parent)
	QAsyncSettingsLoader();

	bool isAsync() const final;

public slots:
	//! Will be called asynchronously to load data from the objects thread
	virtual void loadData() = 0;
	//! Will be called asynchronously to save data to the objects thread
	virtual void saveData(const QVariant &data) = 0;
	//! Will be called asynchronously to reset data to the objects thread
	virtual void resetData() = 0;

signals:
	//! Has to be emitted when loading was completed
	void loadDone(bool successful, const QVariant &data, bool isUserEdited = true);
	//! Has to be emitted when saving was completed
	void saveDone(bool successful);
	//! Has to be emitted when resetting was completed
	void resetDone(bool successful);
};
//! @}

#endif // QSETTINGSLOADER_H
