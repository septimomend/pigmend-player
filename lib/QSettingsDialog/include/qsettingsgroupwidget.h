#ifndef QSETTINGSGROUPWIDGET_H
#define QSETTINGSGROUPWIDGET_H

#include "qsettingsdialog_global.h"
#include "qsettingsentry.h"
#include <QHash>
class QSettingsWidgetBase;
class QCheckBox;

//! The base class for group widgets in the settings dialog @ingroup grp_dialogui
class QSETTINGSDIALOGSHARED_EXPORT QSettingsGroupWidgetBase
{
public:
	//! Virtual destructor
	virtual ~QSettingsGroupWidgetBase();

	//! Must return this as QWidget (a cast)
	virtual QWidget *asWidget() = 0;
	//! Will be called to initialize the widgets properties with the given ones
	virtual void initialize(const UiPropertyMap &uiPropertyMap) = 0;

	//! Will be called to set the name (title) of the group
	virtual void setName(const QString &name) = 0;
	//! Will be called to set the tooltip of the group
	virtual void setTooltip(const QString &tooltip) = 0;
	//! Will be called to set the group optional or required
	virtual void setOptional(bool optional) = 0;

	//! Returns whether the group is checked or not
	virtual bool isChecked() const = 0;
	//! Sets the groups checked state
	virtual void setChecked(bool checked) = 0;

	//! Adds a widget to the dialog in a raw way.
	virtual void addWidgetRaw(QSharedPointer<QSettingsEntry> entry, QWidget *content, bool hasError);
	//! Sets an entry within the dialog to be checked
	virtual void setEntryChecked(QSharedPointer<QSettingsEntry> entry, bool checked);
	//! Enables or disables an entry (and it's label) in the group
	virtual void setEntryLabelEnabled(QSharedPointer<QSettingsEntry> entry, bool enabled);
	//! Will be called to find out whether one entry within the group is checked
	virtual bool isEntryChecked(QSharedPointer<QSettingsEntry> entry) const;

	//! Called to search for the expression within the group and it's children
	virtual bool searchExpression(const QRegularExpression &regex, const QString &searchStyleSheet);

protected:
	//! Simple way to add widgets with a label to the group
	virtual void addWidgetWithLabel(QWidget *label, QWidget *content) = 0;

	//! Defines one "element" within the group - label and edit widget
	typedef QPair<QWidget*, QSettingsWidgetBase*> GroupElement;
	//! A map that contains all elements withing this group, by their entry
	QHash<QSharedPointer<QSettingsEntry>, GroupElement> entryMap;
};

//! Generic base class for group widgets @ingroup grp_dialogui
template <class TWidget>
class QSettingsGroupWidget : public TWidget, public QSettingsGroupWidgetBase
{
public:
	//! Creates a new group widget with a parent
	inline QSettingsGroupWidget(QWidget *parent = nullptr) :
		TWidget(parent),
		QSettingsGroupWidgetBase()
	{}

	inline QWidget *asWidget() final {
		return this;
	}
	void initialize(const UiPropertyMap &uiPropertyMap) override {
		for(UiPropertyMap::const_iterator it = uiPropertyMap.constBegin(), end = uiPropertyMap.constEnd(); it != end; ++it)
			this->setProperty(it.key().toLocal8Bit().constData(), it.value());
	}
};

#endif // QSETTINGSGROUPWIDGET_H
