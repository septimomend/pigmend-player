#ifndef QSETTINGSEXTENDEDTYPES_H
#define QSETTINGSEXTENDEDTYPES_H

#include <QString>
#include <QObject>
#include <QVariant>

//! A custom type that represents a file path (is a QString) @ingroup grp_variantwidgets
class FilePath : public QString
{
public:
	//! Creates a FilePath by passing the arguments to the QString constructor
	template <typename... Args>
	FilePath(Args... args) :
		QString(args...)
	{}

	//! QVariant Converter
	operator QVariant() {
		return (QString)*this;
	}
};

//! A custom type that represents an integer range (is an int) @ingroup grp_variantwidgets
class IntRange
{
public:
	//! Creates a IntRange from a value
	IntRange(int value = 0) :
		value(value)
	{}

	//! Converter to int
	operator int() {
		return this->value;
	}

	//! QVariant Converter
	operator QVariant() {
		return this->value;
	}

	//! assignment operator from int
	IntRange &operator=(int value) {
		this->value = value;
		return (*this);
	}

private:
	int value;
};

//! A custom type that represents html-text (is a QString) @ingroup grp_variantwidgets
class HtmlText : public QString
{
public:
	//! Creates a HtmlText by passing the arguments to the QString constructor
	template <typename... Args>
	HtmlText(Args... args) :
		QString(args...)
	{}

	//! QVariant Converter
	operator QVariant() {
		return (QString)*this;
	}
};

Q_DECLARE_METATYPE(FilePath)
Q_DECLARE_METATYPE(IntRange)
Q_DECLARE_METATYPE(HtmlText)

#endif // QSETTINGSEXTENDEDTYPES_H
