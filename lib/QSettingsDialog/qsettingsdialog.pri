CONFIG(debug, debug|release): CONFIG += add_rpath

win32 {
	msvc {
		contains(QT_ARCH, x86_64) {
			CONFIG(release, debug|release): LIBS += -L$$PWD/msvc64/release/ -lQSettingsDialog
			else:CONFIG(debug, debug|release): LIBS += -L$$PWD/msvc64/debug/ -lQSettingsDialog
		} else {
			CONFIG(release, debug|release): LIBS += -L$$PWD/msvc/release/ -lQSettingsDialog
			else:CONFIG(debug, debug|release): LIBS += -L$$PWD/msvc/debug/ -lQSettingsDialog
		}
	} else:win32-g++ {
		CONFIG(release, debug|release): LIBS += -L$$PWD/mingw/release/ -lQSettingsDialog
		else:CONFIG(debug, debug|release): LIBS += -L$$PWD/mingw/debug/ -lQSettingsDialog
	}
} else:mac:contains(QT_ARCH, x86_64) {
	CONFIG(release, debug|release) {
		QMAKE_LFLAGS += -F$$PWD/clang64/release/
		add_rpath: QMAKE_LFLAGS += '-Wl,-rpath,\'$$PWD/clang64/release\''
		LIBS += -F$$PWD/clang64/release/ -framework QSettingsDialog
	} else:CONFIG(debug, debug|release) {
		QMAKE_LFLAGS += -F$$PWD/clang64/debug/
		add_rpath: QMAKE_LFLAGS += '-Wl,-rpath,\'$$PWD/clang64/debug\''
		LIBS += -F$$PWD/clang64/debug/ -framework QSettingsDialog
	}
} else:unix:!mac:contains(QT_ARCH, x86_64) {
	CONFIG(release, debug|release) {
		add_rpath: QMAKE_LFLAGS += '-Wl,-rpath,\'$$PWD/gcc64/release\''
		LIBS += -L$$PWD/gcc64/release/ -lQSettingsDialog
	} else:CONFIG(debug, debug|release) {
		add_rpath: QMAKE_LFLAGS += '-Wl,-rpath,\'$$PWD/gcc64/debug\''
		LIBS += -L$$PWD/gcc64/debug/ -lQSettingsDialog
	}
}

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
