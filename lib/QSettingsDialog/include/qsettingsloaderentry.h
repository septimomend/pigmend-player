#ifndef QSETTINGSLOADERENTRY_H
#define QSETTINGSLOADERENTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingsentry.h"
#include "qsettingsloader.h"

//! A combination of a QSettingsEntry and a QSimpleSettingsLoader in one class \ingroup grp_core
class QSettingsLoaderEntry : public QSettingsEntry, public QSimpleSettingsLoader
{
public:
	//! Creates a new loader entry from a display id
	inline QSettingsLoaderEntry(int displaytype) :
		QSettingsEntry(displaytype, nullptr)
	{}
	//! Creates a new loader entry from a display id and it's properties
	QSettingsLoaderEntry(int displaytype,
						 const QString &name,
						 bool optional = false,
						 const QString &tooltip = QString(),
						 const UiPropertyMap &properties = UiPropertyMap()) :
		QSettingsEntry(displaytype, nullptr, name, optional, tooltip, properties)
	{}
	//! Creates a new loader entry from a display id and it's properties
	template<typename... Args>
	QSettingsLoaderEntry(int displaytype,
						 const QString &name,
						 bool optional,
						 const QString &tooltip,
						 Args... properties) :
		QSettingsEntry(displaytype, nullptr, name, optional, tooltip, properties...)
	{}

	inline QSettingsLoader *getLoader() final {
		return this;
	}
	inline void freeLoader(QSettingsLoader *) final {}
};

#endif // QSETTINGSLOADERENTRY_H
