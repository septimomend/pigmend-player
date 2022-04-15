#ifndef VARIANTWIDGETSREGISTRATOR_H
#define VARIANTWIDGETSREGISTRATOR_H

#include "qsettingsdialog_global.h"

//! Enviroment variable name for autoload configuration @ingroup grp_variantwidgets
#define VARIANT_WIDGETS_AUTOLOAD "env_qsettingsdialog_autoload"
//! Enviroment variable value to autoload groups @ingroup grp_variantwidgets
#define AUTOLOAD_GROUPS 0b1000
//! Enviroment variable value to autoload default edit widgets @ingroup grp_variantwidgets
#define AUTOLOAD_WIDGETS 0b0100
//! Enviroment variable value to autoload enum factories @ingroup grp_variantwidgets
#define AUTOLOAD_ENUMS 0b0010
//! Enviroment variable value to autoload extended edit widgets @ingroup grp_variantwidgets
#define AUTOLOAD_EXTENDED 0b0001

//! A static class to globally register different types of edit widgets @ingroup grp_variantwidgets
class QSETTINGSDIALOGSHARED_EXPORT VariantWidgetsRegistrator
{
public:
	//! Registeres the default group widgets
	static void registerGroupWidgets();
	//! Registeres the default edit widgets
	static void registerVariantWidgets();
	//! Registeres the enum and flag edit widget facotries
	static void registerEnumFactories();
	//! Registeres the extended edit widgets
	static void registerExtendedVariantWidgets();
};

#endif // VARIANTWIDGETSREGISTRATOR_H
