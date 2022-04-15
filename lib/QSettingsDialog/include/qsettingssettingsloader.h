#ifndef QSETTINGSSETTINGSLOADER_H
#define QSETTINGSSETTINGSLOADER_H

#include "qsettingsdialog_global.h"
#include "qsettingsloader.h"
#include <QSettings>
#include <QScopedPointer>

class QSettingsSettingsLoaderPrivate;
//! A loader to load data from QSettings @ingroup grp_loaders
class QSETTINGSDIALOGSHARED_EXPORT QSettingsSettingsLoader : public QSimpleSettingsLoader
{
public:
	//! Creates a loader for a key in the default QSettings
	QSettingsSettingsLoader(const QString &key);
	//! Creates a loader for a key in given QSettings
	QSettingsSettingsLoader(QSettings *settings, const QString &key, bool ownSettings = false);
	//! Destructor
	~QSettingsSettingsLoader();

	// QSimpleSettingsLoader interface
	bool load(QVariant outParam data, bool outParam userEdited) override;
	bool save(const QVariant &data) override;
	bool reset() override;

	//! Creates a list of loaders for a group in the settings
	static QHash<QString, QSettingsSettingsLoader*> createLoaders(QSettings *settings,
																  const QString &rootKey = QString(),
																  bool recursive = false);

private:
	QScopedPointer<QSettingsSettingsLoaderPrivate> d_ptr;

	static QHash<QString, QSettingsSettingsLoader*> createLoadersImpl(QSettings *settings,
																	  const QString &rootKey,
																	  bool recursive);
};

#endif // QSETTINGSSETTINGSLOADER_H
