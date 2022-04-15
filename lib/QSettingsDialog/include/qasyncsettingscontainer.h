#ifndef QASYNCSETTINGSCONTAINER_H
#define QASYNCSETTINGSCONTAINER_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include "qsettingscontainer.h"

class QAsyncSettingsContainerPrivate;
//! A special class that allows access to the settings dialog from different threads
class QSETTINGSDIALOGSHARED_EXPORT QAsyncSettingsContainer : public QSettingsContainer
{
	Q_OBJECT
public:
	//! Creates a new container for a container at the given path for the given dialog
	explicit QAsyncSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent = nullptr);
	//! Destructor
	~QAsyncSettingsContainer();

	// QSettingsContainer interface
	QSettingsDialog *dialog() const override;
	QString containerPath() const override;

	int elementCount() const override;
	bool isEntry(int index) const override;
	int getEntryIndex(int id) const override;
	int getEntryId(int index) const override;
	QSharedPointer<QSettingsEntry> getEntry(int id) const override;
	QSharedPointer<QSettingsEntry> getEntryFromIndex(int index) const override;

	bool transferElement(int indexFrom, QSettingsContainer *targetContainer, int indexTo) override;

public slots:
	int appendEntry(QSettingsEntry *entry) override;
	int prependEntry(QSettingsEntry *entry) override;
	int insertEntry(int index, QSettingsEntry *entry) override;
	int insertEntry(int index, QSharedPointer<QSettingsEntry> entry) override;
	bool removeEntry(int id) override;
	bool removeElementFromIndex(int index) override;
	void moveElement(int indexFrom, int indexTo) override;
	//! Asynchronously moves the element from the old to the new index
	void moveElementAsync(int indexFrom, int indexTo);

	//! Asynchronously appends the entry to the container
	void appendEntryAsync(QSettingsEntry *entry);
	//! Asynchronously prepends the entry to the container
	void prependEntryAsync(QSettingsEntry *entry);

protected:
	bool acceptEntry(int index, int id, QSharedPointer<QSettingsEntry> entry) override;

private:
	QScopedPointer<QAsyncSettingsContainerPrivate, QScopedPointerDeleteLater> d_ptr;
};

#endif // QASYNCSETTINGSCONTAINER_H
