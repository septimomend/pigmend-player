#ifndef QSETTINGSDIALOG_H
#define QSETTINGSDIALOG_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QString>
#include <QIcon>
#include <QScopedPointer>
#include "exceptions.h"
#include "qsettingsentry.h"
class QSettingsDisplayEngine;
class QSettingsContainer;

class QSettingsDialogPrivate;
//! The main class that represents the dialog itself. \ingroup grp_core
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialog : public QObject
{
	Q_OBJECT
	friend class QSettingsDialogPrivate;

public:
	//! Creates a new settings dialog with a parent
	explicit QSettingsDialog(QObject *parent = nullptr);
	//! Creates a new settings dialog with a parent and a custom display engine
	explicit QSettingsDialog(QSettingsDisplayEngine *engine, QObject *parent = nullptr);
	//! Destructor
	~QSettingsDialog();

	//! Returns the current display engine of dialog
	QSettingsDisplayEngine *displayEngine() const;
	//! Sets the display engine to a new one @own engine
	void setDisplayEngine(QSettingsDisplayEngine *engine);

	//container organisation - getters
	//! Returns the complete current container path
	QString containerPath() const;
	//! Returns the current container path up to the section, excluding groups
	QString sectionContainerPath() const;
	//! Returns the current category id
	QString categoryId() const;
	//! Returns the current section id
	QString sectionId() const;
	//! Returns the current group id
	QString groupId() const;

	//container organisation - setters
	//! Sets the current category and optionally modifies it's appeareance
	void setCategory(const QString &id,
					 const QString &name = QString(),
					 const QIcon &icon = QIcon(),
					 const QString &tooltip = QString());
	//! Sets the current section and optionally modifies it's appeareance
	void setSection(const QString &id,
					const QString &name = QString(),
					const QIcon &icon = QIcon(),
					const QString &tooltip = QString());
	//! Sets the current group and optionally modifies it's appeareance
	void setGroup(const QString &id,
				  int displayId = -1,
				  const QString &name = QString(),
				  int optional = -1,
				  const QString &tooltip = QString());
	//! Sets the current group to nothing
	void unsetGroup();

	//! Sets the whole container path (category, section and (optionally) group)
	void setContainer(const QString &containerPath);
	//! Removes the container with the given path
	bool removeContainer(const QString &containerPath);

	//! Creates a new settings container for the current path configuration
	QSettingsContainer *currentContainer(QObject *parent = nullptr);
	//! Creates a new async settings container for the current path configuration
	QSettingsContainer *currentContainerAsync(QObject *parent = nullptr);
	//! Creates a new settings container for the current section
	QSettingsContainer *currentSectionContainer(QObject *parent = nullptr);
	//! Creates a new async settings container for the current section
	QSettingsContainer *currentSectionContainerAsync(QObject *parent = nullptr);

	//entry organisation
	//! Appends the given entry to the current container
	int appendEntry(QSettingsEntry *entry);
	//! Appends the given entry to to the container specified
	int appendEntry(const QString &containerPath, QSettingsEntry *entry);
	//! Prepends the given entry to the current container
	int prependEntry(QSettingsEntry *entry);
	//! Prepends the given entry to to the container specified
	int prependEntry(const QString &containerPath, QSettingsEntry *entry);

	//! Searches for an entry with the given id
	QSharedPointer<QSettingsEntry> getEntry(int id) const;
	//! Searches for the path of the container of the entry with the given id
	QString getEntryPath(int id) const;
	//! Searches for an entry with the given id and removes it
	bool removeEntry(int id);

	//helper
	//! Creates a container path string from category, section and group
	static QString createContainerPath(QString category = QString(),
									   QString section = QString(),
									   QString group = QString());

public slots:
	//! Creates a new display dialog and shows it without blocking
	void openSettings(QWidget *parentWindow = nullptr);
	//! Creates a new display dialog and shows it blocking
	int execSettings(QWidget *parentWindow = nullptr);

signals:
	//! Will be emitted everytime the user saves his settings.
	void saved(bool closed);
	//! Will be emitted if the user resets the settings
	void resetted();
	//! Will be emitted if the user canceld the settings dialog
	void canceled();

private slots:
	void completed(bool close = true);

private:
	QScopedPointer<QSettingsDialogPrivate> d_ptr;
};

#endif // QSETTINGSDIALOG_H
