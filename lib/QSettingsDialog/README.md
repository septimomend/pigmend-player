# QSettingsDialog
[![BSD3 License](https://img.shields.io/badge/license-BSD3-blue.svg?style=flat)](https://opensource.org/licenses/BSD-3-Clause)

A Qt library to easily create a settings dialog for user configurable settings.

Github repository: https://github.com/Skycoder42/QSettingsDialog

## Main Features
The settings dialog provides a number of classes to create simple to highly customizable settings dialogs. It provides simple, general interfaces to easily create a normal settings dialog, as well as many mechanisms to make it highly customizable and easily extendable.
The library is split into four logical modules, based on concern.

### Core-Module
The core module is responsible for the definition of the base classes and the managemant behind the dialog. It's main features are:
- A central class for simple dialog creation
- Advanced classes to control the appeareance and allow encapsualted and threaded access to the dialog
- Abstraction from the actual ui, by using a defined logical structure of entry organization
- Provides interfaces to allow a completly customized UI

### Dialog-UI-Module
This module provides the standard widgets based dialog ui, as well the interfaces needed to customize appeareance and possible edit widgets:
- Generic dialog ui, for all 3 Desktop platforms
- Interfaces for custom entry groups
- Interfaces for custom edit widgets

### Variantwidgets-Module
This module contains a collection of default and advanced edit widgets for standard types and others:
- Seperation of different edit groups
- Supports all basic datatypes, enums, flags and a few specialized custom types

### Loaders-Module
This module contains a number of custom settings datasources, to load settings entries from:
- Provides loading from QSettings
- Provides loading from QObject properties

## Images
| Windows                                                       | Mac                                                           | X11                                                           |
|---------------------------------------------------------------|---------------------------------------------------------------|---------------------------------------------------------------|
| ![Sample Dialog](./QSettingsDialog/doc/images/win_sample.png) | ![Sample Dialog](./QSettingsDialog/doc/images/mac_sample.png) | ![Sample Dialog](./QSettingsDialog/doc/images/x11_sample.png) |

## Gettings Started
The library provides many features, and with this come a bunch of classes to provide all these possibilities. To get started, there are only very few of them you will work with:
- QSettingsDialog
- QSettingsEntry
- QSettingsPropertyLoader (-Entry)
- QSettingsSettingsLoader
- "Display-Ids"

They work together as following: The dialog is the core of everything. You will add entries to it, representing one entry in the dialog. Each entry has one loader attached, that will be used to load and save the actual data. To display an appropriate edit widget, a display id will be assigned to the entry and used to resolve the edit widget.

A very basic example looks like this:
```.cpp
#include <QApplication>
#include <qsettingsdialog.h>
#include <qsettingssettingsloader.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettings settings(QApplication::applicationDirPath() + "/test.ini", QSettings::IniFormat);

	//create the dialog
	QSettingsDialog dialog;
	
	// add a new entry
	dialog.appendEntry(new QSettingsEntry(QMetaType::QString,// <- The display id. In this case, an edit for a QString is loaded, a QLineEdit
										  new QSettingsSettingsLoader(&settings, "appName"),// <- The loader loads a value with the key "appName" from the settings
										  "App name"));//Other properties of the entry, i.e. The label text
	
	//show the dialog (blocking)
	return dialog.execSettings();
}
```

For more advanced examples, check the examples subfolder of the project and the documentation. 

## Documentation
The documentation is available within the releases and on [github pages](https://skycoder42.github.io/QSettingsDialog/).

The documentation was created using [doxygen](http://www.stack.nl/~dimitri/doxygen/). It includes an HTML-documentation and Qt-Help files that can be included into QtCreator (QtAssistant) to show F1-Help (See [Adding External Documentation](https://doc.qt.io/qtcreator/creator-help.html#adding-external-documentation) for more details).

## Translation
Comming soon. The code is prepared, but that's it for know.

## Downloads
Downloads are available via [github releases](https://github.com/Skycoder42/QSettingsDialog/releases). The downloads include:
 - A .pri file for easy project includes (Just add `include(<path_to>/qsettingsdialog.pri)` to your project and all the includes/libray imports/... will be done by that file!)
 - Qt5.7 precompiled binaries for:
   - Windows
	 - msvc2015 x86
	 - msvc2015 x64
	 - minGw 5.3.0 32bit
   - OsX
     - clang x64
   - X11 (Linux)
     - gcc x64
 - The (public) header files needed for these binaries
 - The HTML and QtHelp documentation (in the first full release)
 - The german translations and the translation template file (in the first full release)

## Submodules
The library makes use of three submodules:
- https://github.com/Skycoder42/DialogMaster
- https://github.com/Skycoder42/QPathEdit
- https://github.com/Skycoder42/QColorEdit
 
## Icon sources/Links
All icons come from http://www.fatcow.com/free-icons
