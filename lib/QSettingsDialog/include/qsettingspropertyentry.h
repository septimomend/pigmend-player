#ifndef QSETTINGSPROPERTYENTRY_H
#define QSETTINGSPROPERTYENTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingsentry.h"
class QSettingsPropertyLoader;

//! A class that combines the QSettingsEntry and the QSettingsPropertyLoader @ingroup grp_loaders
class QSETTINGSDIALOGSHARED_EXPORT QSettingsPropertyEntry : public QSettingsEntry
{
public:
	//! Creates a property entry for a property on an object
	explicit QSettingsPropertyEntry(const char *propertyName, QObject *object);
	//! Creates a property entry for a property on an object
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty, QObject *object);
	//! Creates a property entry for a property on a gadget, with the gadgets static metaobject
	explicit QSettingsPropertyEntry(const char *propertyName, QMetaObject *metaObject, void *gadget);
	//! Creates a property entry for a property on a gadget
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty, void *gadget);

	//! Creates a property entry for a property on an object, with entry properties
	explicit QSettingsPropertyEntry(const char *propertyName,
									QObject *object,
									const QString &name,
									bool optional = false,
									const QString &tooltip = QString(),
									const UiPropertyMap &properties = UiPropertyMap());
	//! Creates a property entry for a property on an object, with entry properties
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty,
									QObject *object,
									const QString &name,
									bool optional = false,
									const QString &tooltip = QString(),
									const UiPropertyMap &properties = UiPropertyMap());
	//! Creates a property entry for a property on a gadget, with the gadgets static metaobject, with entry properties
	explicit QSettingsPropertyEntry(const char *propertyName,
									QMetaObject *metaObject,
									void *gadget,
									const QString &name,
									bool optional = false,
									const QString &tooltip = QString(),
									const UiPropertyMap &properties = UiPropertyMap());
	//! Creates a property entry for a property on a gadget, with entry properties
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty,
									void *gadget,
									const QString &name,
									bool optional = false,
									const QString &tooltip = QString(),
									const UiPropertyMap &properties = UiPropertyMap());

	//! Creates a property entry for a property on an object, with entry properties
	template<typename... Args>
	explicit QSettingsPropertyEntry(const char *propertyName,
									QObject *object,
									const QString &name,
									bool optional,
									const QString &tooltip,
									Args... properties);
	//! Creates a property entry for a property on an object, with entry properties
	template<typename... Args>
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty,
									QObject *object,
									const QString &name,
									bool optional,
									const QString &tooltip,
									Args... properties);
	//! Creates a property entry for a property on a gadget, with the gadgets static metaobject, with entry properties
	template<typename... Args>
	explicit QSettingsPropertyEntry(const char *propertyName,
									QMetaObject *metaObject,
									void *gadget,
									const QString &name,
									bool optional,
									const QString &tooltip,
									Args... properties);
	//! Creates a property entry for a property on a gadget, with entry properties
	template<typename... Args>
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty,
									void *gadget,
									const QString &name,
									bool optional,
									const QString &tooltip,
									Args... properties);

	int displaytype() override;
};


template<typename... Args>
QSettingsPropertyEntry::QSettingsPropertyEntry(const char *propertyName, QObject *object, const QString &name, bool optional, const QString &tooltip, Args... properties) :
    QSettingsPropertyEntry(propertyName, object, name, optional, tooltip, mapWrapper(properties...))
{}

template<typename... Args>
QSettingsPropertyEntry::QSettingsPropertyEntry(const QMetaProperty &metaProperty, QObject *object, const QString &name, bool optional, const QString &tooltip, Args... properties) :
    QSettingsPropertyEntry(metaProperty, object, name, optional, tooltip, mapWrapper(properties...))
{}

template<typename... Args>
QSettingsPropertyEntry::QSettingsPropertyEntry(const char *propertyName, QMetaObject *metaObject, void *gadget, const QString &name, bool optional, const QString &tooltip, Args... properties) :
	QSettingsPropertyEntry(propertyName, metaObject, gadget, name, optional, tooltip, mapWrapper(properties...))
{}

template<typename... Args>
QSettingsPropertyEntry::QSettingsPropertyEntry(const QMetaProperty &metaProperty, void *gadget, const QString &name, bool optional, const QString &tooltip, Args... properties) :
    QSettingsPropertyEntry(metaProperty, gadget, name, optional, tooltip, mapWrapper(properties...))
{}

#endif // QSETTINGSPROPERTYENTRY_H
