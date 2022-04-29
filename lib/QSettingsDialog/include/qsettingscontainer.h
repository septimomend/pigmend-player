#ifndef QSETTINGSCONTAINER_H
#define QSETTINGSCONTAINER_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QScopedPointer>
#include "qsettingsentry.h"
#include "exceptions.h"
class QSettingsDialog;
class QSettingsLayout;

//! A generic class the defines methods for settings containers @ingroup grp_core
class QSETTINGSDIALOGSHARED_EXPORT QSettingsContainer : public QObject
{
	Q_OBJECT

public:
	//! Returns the dialog this container belongs to
	virtual QSettingsDialog *dialog() const = 0;
	//! Returns the container path this container has
	virtual QString containerPath() const = 0;

	//! Returns the number of elements in this container
	virtual int elementCount() const = 0;
	//! Checks whether the element at the given index is an entry or not
	virtual bool isEntry(int index) const = 0;
	//! Searches for entries index
	virtual int getEntryIndex(int id) const = 0;
	//! Returns the id for the entry at the index
	virtual int getEntryId(int index) const = 0;
	//! Returns the entry with the given id
	virtual QSharedPointer<QSettingsEntry> getEntry(int id) const = 0;
	//! Returns the entry at the given index
	virtual QSharedPointer<QSettingsEntry> getEntryFromIndex(int index) const = 0;

	//! Tries to transfer the element at index to the target container
	virtual bool transferElement(int indexFrom, QSettingsContainer *targetContainer, int indexTo) = 0;

public slots:
	//! Appends the entry to the containers children @own entry
	virtual int appendEntry(QSettingsEntry *entry) = 0;
	//! Prepends the entry to the containers children @own entry
	virtual int prependEntry(QSettingsEntry *entry) = 0;
	//! Inserts the entry to the containers children at the given index @own entry
	virtual int insertEntry(int index, QSettingsEntry *entry) = 0;
	//! Appends the entry to the containers children at the given index
	virtual int insertEntry(int index, QSharedPointer<QSettingsEntry> entry) = 0;

	//! Removes the entry with the given id
	virtual bool removeEntry(int id) = 0;
	//! Removes the element at the given index
	virtual bool removeElementFromIndex(int index) = 0;
	//! Moves the element from the old to the new index
	virtual void moveElement(int indexFrom, int indexTo) = 0;

protected:
	//! Protected constructor
	inline QSettingsContainer(QObject *parent = nullptr) :
		QObject(parent)
	{}

	//! Will be called to insert the given entry from a transfer
	virtual bool acceptEntry(int index, int id, QSharedPointer<QSettingsEntry> entry) = 0;
	//! @intuse Helper function
	inline bool doAccept(QSettingsContainer *target, int index, int id, QSharedPointer<QSettingsEntry> entry) {
		return target->acceptEntry(index, id, entry);
	}
};

class QSectionSettingsContainer;
class QGroupSettingsContainerPrivate;
//! A settings container for groups @ingroup grp_core
class QSETTINGSDIALOGSHARED_EXPORT QGroupSettingsContainer : public QSettingsContainer
{
	Q_OBJECT

public:
	//! Creates a new container for a container at the given path for the given dialog
	explicit QGroupSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent = nullptr);
	//! Creates a new container from a settings layout
	explicit QGroupSettingsContainer(const QSettingsLayout &layout, QObject *parent = nullptr);
	//! Destructor
	~QGroupSettingsContainer();

	QSettingsDialog *dialog() const override;
	QString containerPath() const override;

	int elementCount() const override;
	bool isEntry(int index) const override;
	int getEntryIndex(int id) const override;
	int getEntryId(int index) const override;
	QSharedPointer<QSettingsEntry> getEntry(int id) const override;
	QSharedPointer<QSettingsEntry> getEntryFromIndex(int index) const override;

	bool transferElement(int indexFrom, QSettingsContainer *targetContainer, int indexTo) override;

	//! Creates a new container for this groups section
	QSectionSettingsContainer *parentSection();
	//! Creates a new container for this groups section
	QSectionSettingsContainer *parentSection(QObject *parent) const;

public slots:
	int appendEntry(QSettingsEntry *entry) override;
	int prependEntry(QSettingsEntry *entry) override;
	int insertEntry(int index, QSettingsEntry *entry) override;
	int insertEntry(int index, QSharedPointer<QSettingsEntry> entry) override;

	bool removeEntry(int id) override;
	bool removeElementFromIndex(int index) override;
	void moveElement(int indexFrom, int indexTo) override;

protected:
	bool acceptEntry(int index, int id, QSharedPointer<QSettingsEntry> entry) override;

private:
	QScopedPointer<QGroupSettingsContainerPrivate> d_ptr;
};

class QSectionSettingsContainerPrivate;
//! A settings container for sections @ingroup grp_core
class QSETTINGSDIALOGSHARED_EXPORT QSectionSettingsContainer : public QSettingsContainer
{
	Q_OBJECT

public:
	//! Creates a new container for a container at the given path for the given dialog
	explicit QSectionSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent = nullptr);
	//! Creates a new container from a settings layout
	explicit QSectionSettingsContainer(const QSettingsLayout &layout, QObject *parent = nullptr);
	//! Destructor
	~QSectionSettingsContainer();

	QSettingsDialog *dialog() const override;
	QString containerPath() const override;

	int elementCount() const override;
	bool isEntry(int index) const override;

	int getEntryIndex(int id) const override;
	//! Searches for groups index
	int getGroupIndex(const QString &id) const;

	//! Returns the id for the element at the index
	QVariant getElementId(int index) const;
	int getEntryId(int index) const override;
	//! Returns the id for the group at the index
	QString getGrouptId(int index) const;

	QSharedPointer<QSettingsEntry> getEntry(int id) const override;
	QSharedPointer<QSettingsEntry> getEntryFromIndex(int index) const override;

	bool transferElement(int indexFrom, QSettingsContainer *targetContainer, int indexTo) override;

	//! Creates a new container for the child group with the given id
	QGroupSettingsContainer *createGroupContainer(const QString &id);
	//! Creates a new container for the child group with the given id
	QGroupSettingsContainer *createGroupContainer(const QString &id, QObject *parent) const;
	//! Creates a new container for the child group at the given index
	QGroupSettingsContainer *createGroupContainerFromIndex(int index);
	//! Creates a new container for the child group at the given index
	QGroupSettingsContainer *createGroupContainerFromIndex(int index, QObject *parent) const;

public slots:
	int appendEntry(QSettingsEntry *entry) override;
	int prependEntry(QSettingsEntry *entry) override;
	int insertEntry(int index, QSettingsEntry *entry) override;
	int insertEntry(int index, QSharedPointer<QSettingsEntry> entry) override;

	//! Creates and appends a new group to the containers children
	void appendGroup(const QString &id,
					 int displayId = 0,
					 const QString &name = QString(),
					 bool optional = false,
					 const QString &tooltip = QString());
	//! Creates and prepends a new group to the containers children
	void prependGroup(const QString &id,
					  int displayId = 0,
					  const QString &name = QString(),
					  bool optional = false,
					  const QString &tooltip = QString());
	//! Creates and inserts a new group to the containers children at the given index
	void insertGroup(int index,
					 const QString &id,
					 int displayId = 0,
					 const QString &name = QString(),
					 bool optional = false,
					 const QString &tooltip = QString());

	bool removeEntry(int id) override;
	//! Removes the group with the given id
	bool removeGroup(const QString &id);
	bool removeElementFromIndex(int index) override;
	void moveElement(int indexFrom, int indexTo) override;

protected:
	bool acceptEntry(int index, int id, QSharedPointer<QSettingsEntry> entry) override;

private:
	QScopedPointer<QSectionSettingsContainerPrivate> d_ptr;
};

#endif // QSETTINGSCONTAINER_H
