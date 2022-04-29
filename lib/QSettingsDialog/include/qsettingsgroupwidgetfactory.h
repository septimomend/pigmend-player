#ifndef QSETTINGSGROUPWIDGETFACTORY_H
#define QSETTINGSGROUPWIDGETFACTORY_H

#include "qsettingsdialog_global.h"
#include "qsettingsgroupwidget.h"

//! The base class for a factory to create QSettingsGroupWidgets @ingroup grp_dialogui
class QSETTINGSDIALOGSHARED_EXPORT QSettingsGroupWidgetFactory
{
public:
	//! Virtual destructor
	inline virtual ~QSettingsGroupWidgetFactory() {}

	//! Creates a new instance of the group widget
	virtual QSettingsGroupWidgetBase *createGroupWidget(QWidget *parent) = 0;
};

//! @intuse Generic base class for a factory to create QSettingsWidgets @ingroup grp_dialogui
template <class TSettingsGroupWidget>
class GenericSettingsGroupWidgetFactory : public QSettingsGroupWidgetFactory
{
public:
	QSettingsGroupWidgetBase *createGroupWidget(QWidget *parent) final {
		return new TSettingsGroupWidget(parent);
	}
};

#endif // QSETTINGSGROUPWIDGETFACTORY_H
