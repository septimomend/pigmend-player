#ifndef QSETTINGSWIDGETFACTORY_H
#define QSETTINGSWIDGETFACTORY_H

#include "qsettingsdialog_global.h"
#include "qsettingswidget.h"

//! The base class for a factory to create QSettingsWidgets @ingroup grp_dialogui
class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetFactory
{
public:
	//! Virtual destructor
	inline virtual ~QSettingsWidgetFactory() {}

	//! Creates a new instance of the settings widget
	virtual QSettingsWidgetBase *createWidget(QWidget *parent) = 0;
};

//! @intuse Generic base class for a factory to create QSettingsWidgets @ingroup grp_dialogui
template <class TSettingsWidget>
class GenericSettingsWidgetFactory : public QSettingsWidgetFactory
{
public:
	QSettingsWidgetBase *createWidget(QWidget *parent) final {
		return new TSettingsWidget(parent);
	}
};

//! A macro for type converter registration @ingroup grp_dialogui
#define REGISTER_TYPE_CONVERTERS(TypeA, TypeB) do {\
	QMetaType::registerConverter<TypeA, TypeB>([](TypeA aVal) -> TypeB {\
		return (TypeB)aVal;\
	});\
	QMetaType::registerConverter<TypeB, TypeA>([](TypeB bVal) -> TypeA {\
		return TypeA(bVal);\
	});\
} while(false)

//! A macro to register flag types @ingroup grp_dialogui
#define REGISTER_FLAG_CONVERTERS(FlagsType) REGISTER_TYPE_CONVERTERS(FlagsType, int)

#endif // QSETTINGSWIDGETFACTORY_H
