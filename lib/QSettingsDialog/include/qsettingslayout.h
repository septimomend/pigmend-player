#ifndef QSETTINGSLAYOUT_H
#define QSETTINGSLAYOUT_H

#include "qsettingsdialog_global.h"
#include "exceptions.h"
#include <QObject>
#include <QList>
#include <QIcon>
#include <QSharedPointer>
class QSettingsDialog;
class QSettingsContainer;

class QSettingsLayoutPrivate;
//! A general class to modifiy the appereance of elements of a settings dialog @ingroup grp_core
class QSETTINGSDIALOGSHARED_EXPORT QSettingsLayout
{
	friend class SettingsEntryLayout;
	friend class SettingsGroupLayout;
	friend class SettingsSectionLayout;
	friend class SettingsCategoryLayout;
	friend class SettingsRootLayout;

public:
	//! Defines the different elements a layout can be created for
	enum LayoutType {
		DialogLayout, //!< The layout represents the dialog itself
		CategoryLayout, //!< The layout represents a category
		SectionLayout, //!< The layout represents a section
		GroupLayout, //!< The layout represents a group
		EntryLayout //!< The layout represents an entry
	};

	//! Creates a new layout for the given dialogs root element or current container
	explicit QSettingsLayout(QSettingsDialog *settingsDialog, bool fromCurrentContainer = false);
	//! Creates a new layout for the given container in the dialog or an entry within that container
	explicit QSettingsLayout(QSettingsDialog *settingsDialog, const QString &containerPath, int entryId = -1);
	//! Creates a new layout from the given container
	explicit QSettingsLayout(QSettingsContainer *container);

	//! Returns the container id of the current container
	QString id() const;
	//! Returns the element type this layout represents
	LayoutType layoutType() const;
	//! Returns whether this layout is a null-layout (does not represent anything)
	bool isNull() const;

	//! Returns the dialog this layout belongs to
	QSettingsDialog *dialog() const;
	//! Returns the full container path of the element
	QString containerPath() const;

	//! Returns the parent container element, if available
	QSettingsLayout parentContainer() const;

	//! Gets the elements display id
	int displayId() const;
	//! Sets the elements display id
	void setDisplayId(int displayId);
	//! Gets the elements name
	QString name() const;
	//! Sets the elements name
	void setName(const QString &name);
	//! Gets the elements icon
	QIcon icon() const;
	//! Sets the elements icon
	void setIcon(const QIcon &icon);
	//! Gets the elements tooltip
	QString tooltip() const;
	//! Sets the elements tooltip
	void setTooltip(const QString &tooltip);
	//! Gets whether the element is optional or not
	bool isOptional() const;
	//! Sets whether the element is optional or not
	void setOptional(bool optional);

	//! Returns the elements default child element
	QSettingsLayout defaultElement(bool allowCreateNew = false) const;
	//! Removes the default element, if it exists
	bool removeDefaultElement();

	//! Returns the number of children this element has
	int elementCount() const;
	//! Gets the child element at the given position
	QSettingsLayout elementAt(int index) const;
	//! Gets the child index of the given element within this element
	int indexOfElement(const QSettingsLayout &element) const;
	//! Gets the child index of the given element by name within this element
	int indexOfElement(const QString &elementName) const;
	//! Creates a new child element at the given index
	QSettingsLayout createElement(int index,
								  const QString &id,
								  const QString &name = QString(),
								  const QIcon &icon = QIcon(),
								  const QString &tooltip = QString());	
	//! Creates a new optional child element at the given index
	QSettingsLayout createGroupElement(int index,
									   const QString &id,
									   int displayId = 0,
									   const QString &name = QString(),
									   bool optional = false,
									   const QString &tooltip = QString());
	//! Removes the child element at the given index
	void removeElement(int index);
	//! Moves the child from one index to a new one
	void moveElement(int indexFrom, int indexTo);

	//! Transfers a child from this layout to the given target
	void transferElement(int indexFrom, QSettingsLayout targetLayout, int indexTo);

private:
	QSharedPointer<QSettingsLayoutPrivate> d_ptr;

	QSettingsLayout(QSettingsLayoutPrivate *d_ptr);
};

#endif // QSETTINGSLAYOUT_H
