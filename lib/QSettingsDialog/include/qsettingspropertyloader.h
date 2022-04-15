#ifndef QSETTINGSPROPERTYLOADER_H
#define QSETTINGSPROPERTYLOADER_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QMetaProperty>
#include <QScopedPointer>
#include "qsettingsloader.h"

class QSettingsPropertyLoaderPrivate;
//! A loader to load properties from objects and gadgets @ingroup grp_loaders
class QSETTINGSDIALOGSHARED_EXPORT QSettingsPropertyLoader : public QAsyncSettingsLoader
{
	Q_OBJECT

public:
	//! Creates a loader for a property on an object
	explicit QSettingsPropertyLoader(const char *propertyName, QObject *object);
	//! Creates a loader for a property on an object
	explicit QSettingsPropertyLoader(const QMetaProperty &metaProperty, QObject *object);
	//! Creates a loader for a property on an gadget, with the gadgets static metaobject
	explicit QSettingsPropertyLoader(const char *propertyName, QMetaObject *metaObject, void *gadget);
	//! Creates a loader for a property on an gadget
	explicit QSettingsPropertyLoader(const QMetaProperty &metaProperty, void *gadget);
	//! Destructor
	~QSettingsPropertyLoader();

	//! Returns the properties metatype id. Can be used for the QSettingsEntry
	int metatypeId() const;
	//! Returns whether the constructed loader points to a valid property on a valid object/gadget
	bool isValid() const;

public slots:	
	// QAsyncSettingsLoader interface
	void loadData() override;
	void saveData(const QVariant &data) override;
	void resetData() override;

private:
	QScopedPointer<QSettingsPropertyLoaderPrivate> d_ptr;
};

#endif // QSETTINGSPROPERTYLOADER_H
