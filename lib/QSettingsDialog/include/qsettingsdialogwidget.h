#ifndef QSETTINGSDIALOGWIDGET_H
#define QSETTINGSDIALOGWIDGET_H

#include "qsettingsdialog_global.h"
#include "qsettingswidget.h"
#include <QWidget>
#include <QDialog>
#include <QIcon>
class QPushButton;

//! The base class for dialog based edit widgets in the settings dialog @ingroup grp_dialogui
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialogWidgetBase : public QSettingsWidget<QWidget>
{
public:
	//! Creates a new dialog widget with a parent
	QSettingsDialogWidgetBase(QWidget *parent = nullptr);

	//! Returns the text to be shown in the dialog button
	virtual QString buttonText() const = 0;
	//! Returns the icon to be shown in the dialog button
	virtual QIcon buttonIcon() const;
	//! Will be called to show the dialog
	virtual void showDialog() = 0;

protected:
	//! Overwritten to load button data when showed
	void showEvent(QShowEvent *event) final;

	//! Helper to "wrap" any widget inside a dialog
	static void wrapInDialog(QDialog *dialog, QWidget *element, bool fixedSize = false);

private:
	QPushButton *btn;
};

//! A generic class to easily create a dialog widget from a normal one @ingroup grp_dialogui
template<typename TSettingsWidget>
class QSettingsDialogWidget : public QSettingsDialogWidgetBase
{
public:
	//! Creates a new dialog widget with a parent
	QSettingsDialogWidget(QWidget *parent = nullptr) :
		QSettingsDialogWidgetBase(parent),
		dialog(nullptr),
		widget(new TSettingsWidget(this))
	{
		if(this->widget->inherits("QDialog"))
			this->dialog = (QDialog*)this->widget;
		else {
			this->dialog = new QDialog(this);
			wrapInDialog(this->dialog, this->widget);
		}
	}

	// QSettingsWidgetBase interface
	bool hasValueChanged() const final {
		return this->widget->hasValueChanged();
	}
	void resetValueChanged() final {
		this->widget->resetValueChanged();
	}
	void setValue(const QVariant &value) final {
		this->widget->setValue(value);
	}
	QVariant getValue() const final {
		return this->widget->getValue();
	}
	void resetValue() final {
		this->widget->resetValue();
	}
	bool searchExpression(const QRegularExpression &regex) final {
		return this->widget->searchExpression(regex);
	}

	// QSettingsDialogWidgetBase interface
	QString buttonText() const override {
		return this->widget->windowTitle();
	}
	QIcon buttonIcon() const override {
		return this->widget->windowIcon();
	}
	void showDialog() final {
		this->dialog->open();
	}

private:
	QDialog *dialog;
	TSettingsWidget *widget;
};

#endif // QSETTINGSDIALOGWIDGET_H
