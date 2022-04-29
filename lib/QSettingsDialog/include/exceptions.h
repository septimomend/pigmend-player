#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "qsettingsdialog_global.h"
#include "qtexception.h"

/*!
 * @addtogroup grp_core
 * @{
 */

//! An exception that will be thrown if an invalid container path is used
class QSETTINGSDIALOGSHARED_EXPORT InvalidContainerPathException : public QtException
{
public:
	InvalidContainerPathException();
};

//! An exception that indicates you are trying to access an undefined property in a QSettingsLayout
class QSETTINGSDIALOGSHARED_EXPORT LayoutPropertyNotDefinedException : public QtException
{
public:
	LayoutPropertyNotDefinedException();
};

//! An exception that is thrown if you try to add an element to a QSettingsLayout that does not accept this kind of element
class QSETTINGSDIALOGSHARED_EXPORT InvalidTargetLayoutException : public QtException
{
public:
	InvalidTargetLayoutException();
};
//! @}

#endif // EXCEPTIONS_H
