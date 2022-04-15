#ifndef QSETTINGSWIDGETFACTORYREGISTRY_H
#define QSETTINGSWIDGETFACTORYREGISTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingswidgetfactory.h"
#include <QSharedPointer>

//! A registry to load widget factories based on an id. @ingroup grp_dialogui
class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetFactoryRegistry
{
public:
	//! Virtual Destructor
	inline virtual ~QSettingsWidgetFactoryRegistry() {}

	//! The prioritoy of this registry
	virtual inline int priority() const {
		return 0;
	}
	//! Tries to find a registry for the given id
	virtual QSharedPointer<QSettingsWidgetFactory> tryResolve(int displayId) = 0;
};

#endif // QSETTINGSWIDGETFACTORYREGISTRY_H
