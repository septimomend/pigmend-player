#ifndef QSETTINGSENTRY_H
#define QSETTINGSENTRY_H

#include "qsettingsdialog_global.h"
#include <QScopedPointer>
#include <QHash>
#include "qsettingsloader.h"

class QSettingsEntryPrivate;
//! Represents one settings entry within the settings dialog. \ingroup grp_core
class QSETTINGSDIALOGSHARED_EXPORT QSettingsEntry
{
	friend class SettingsEntryLayout;

public:
	//! Creates a new entry from a display id and a loader @own loader
	QSettingsEntry(int displaytype, QSettingsLoader *loader);
	//! Creates a new entry from a display id, a loader and it's properties @own loader
	QSettingsEntry(int displaytype,
				   QSettingsLoader *loader,
				   const QString &name,
				   bool optional = false,
				   const QString &tooltip = QString(),
				   const UiPropertyMap &properties = UiPropertyMap());
	//! Creates a new entry from a display id, a loader and it's properties @own loader
	template<typename... Args>
	QSettingsEntry(int displaytype,
				   QSettingsLoader *loader,
				   const QString &name,
				   bool optional,
				   const QString &tooltip,
				   Args... properties);
	//! Virtual destructor
	virtual ~QSettingsEntry();

	//! Returns the display name of this entry
	QString entryName() const;
	//! Sets the display name of this entry
	void setEntryName(const QString &name);
	//! Specifies, whether the entry is optional or not
	bool isOptional() const;
	//! Sets the entry be optional or not optional
	void setOptional(bool optional);
	//! Returns the tooltip this entry has
	QString tooltip() const;
	//! Sets this entries tooltip
	void setTooltip(const QString &tooltip);

	//! Returns the properties that should be set on the ui-elements for this entry
	UiPropertyMap uiProperties() const;
	//! Sets the properties that should be set on the ui-elements for this entry
	void setUiProperties(const UiPropertyMap &properties);
	//! Adds a new property to the existing ones that should be set on the ui-elements for this entry
	void setUiProperty(const QString &name, const QVariant &value);

	//! Returns the display type id for this entry
	virtual int displaytype();
	//! Will be called to get a reference to loader this entry holds
	virtual QSettingsLoader *getLoader();
	//! Will be called to remove a reference to the loader this entry holds
	virtual void freeLoader(QSettingsLoader *loader);//TODO required?

private:
	QScopedPointer<QSettingsEntryPrivate> d_ptr;
};



template<typename TVariant>
UiPropertyMap mapWrapper(const char *key, TVariant value) {
	return UiPropertyMap({{key, QVariant::fromValue(value)}});
}

template<typename TVariant, typename... Args>
UiPropertyMap mapWrapper(const char *key, TVariant value, Args... params) {
	auto map = mapWrapper(params...);
	map.insert(key, QVariant::fromValue(value));
	return map;
}

template<typename... Args>
QSettingsEntry::QSettingsEntry(int metatype, QSettingsLoader *loader, const QString &name, bool optional, const QString &tooltip, Args... properties) :
	QSettingsEntry(metatype, loader, name, optional, tooltip, mapWrapper(properties...))
{}

#endif // QSETTINGSENTRY_H
