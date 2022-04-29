CONFIG(debug, debug|release): CONFIG += add_rpath

win32 {
	msvc {
		contains(QT_ARCH, x86_64) {
			CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/QSettingsDialog/msvc64/release/ -lQSettingsDialog
			else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/QSettingsDialog/msvc64/debug/ -lQSettingsDialog
		} else {
			CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/QSettingsDialog/msvc/release/ -lQSettingsDialog
			else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/QSettingsDialog/msvc/debug/ -lQSettingsDialog
		}
	} else:win32-g++ {
		CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/QSettingsDialog/mingw/release/ -lQSettingsDialog
		else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/QSettingsDialog/mingw/debug/ -lQSettingsDialog
	}
} else:mac:contains(QT_ARCH, x86_64) {
	CONFIG(release, debug|release) {
		QMAKE_LFLAGS += -F$$PWD/../lib/QSettingsDialog/clang64/release/
		add_rpath: QMAKE_LFLAGS += '-Wl,-rpath,\'$$PWD/../lib/QSettingsDialog/clang64/release\''
		LIBS += -F$$PWD/../lib/QSettingsDialog/clang64/release/ -framework QSettingsDialog
	} else:CONFIG(debug, debug|release) {
		QMAKE_LFLAGS += -F$$PWD/../lib/QSettingsDialog/clang64/debug/
		add_rpath: QMAKE_LFLAGS += '-Wl,-rpath,\'$$PWD/../lib/QSettingsDialog/clang64/debug\''
		LIBS += -F$$PWD/../lib/QSettingsDialog/clang64/debug/ -framework QSettingsDialog
	}
} else:unix:!mac:contains(QT_ARCH, x86_64) {
	CONFIG(release, debug|release) {
		add_rpath: QMAKE_LFLAGS += '-Wl,-rpath,\'$$PWD/../lib/QSettingsDialog/gcc64/release\''
		LIBS += -L$$PWD/../lib/QSettingsDialog/gcc64/release/ -lQSettingsDialog
	} else:CONFIG(debug, debug|release) {
		add_rpath: QMAKE_LFLAGS += '-Wl,-rpath,\'$$PWD/../lib/QSettingsDialog/gcc64/debug\''
		LIBS += -L$$PWD/../lib/QSettingsDialog/gcc64/debug/ -lQSettingsDialog
	}
}

INCLUDEPATH += $$PWD/../lib/QSettingsDialog/include
DEPENDPATH += $$PWD/../lib/QSettingsDialog/include
