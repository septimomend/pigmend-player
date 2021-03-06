#-------------------------------------------------
#
# Project created by QtCreator 2018-01-23T16:24:02
#
#-------------------------------------------------
#
# GPL-2.0 License
# Copyright (c) 2018 Ivan Chapkailo
#
# See license: https://github.com/septimomend/pigmend-player/blob/feature/PP_1_1/LICENSE
#
# Author: Ivan Chapkailo (https://github.com/septimomend/)
# E-mail: chapkailo.ivan@gmail.com
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PigmendPlayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PRO_FILE_PWD=$$sprintf("\"\\\"%1\\\"\"", $$_PRO_FILE_PWD_)
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mediaplayer.cpp \
    videoWidget.cpp \
    playerControls.cpp \
    playlistSingleton.cpp \
    mediafileController.cpp \
    search.cpp \
    aboutpigmend.cpp \
    ../lib/tinyxml2/tinyxml2.cpp \
    xml-dp/xmldp.cpp \
    config-dp/config.c

HEADERS += \
        mediaplayer.h \
    videoWidget.h \
    playerControls.h \
    playlistSingleton.h \
    mediafileController.h \
    search.h \
    aboutpigmend.h \
    constants.h \
    xml-dp/xmldp.h \
    config-dp/config.h \
    ../lib/rapidxml-1.13/rapidxml_iterators.hpp \
    ../lib/rapidxml-1.13/rapidxml_print.hpp \
    ../lib/rapidxml-1.13/rapidxml_utils.hpp \
    ../lib/rapidxml-1.13/rapidxml.hpp

FORMS += \
        mediaplayer.ui \
    searchdialog.ui \
    aboutpigmend.ui

RESOURCES += \
    playerui.qrc \

win32: RC_FILE += mediaplayer.rc

DISTFILES += \
    mediaplayer.rc

INCLUDEPATH += "../lib"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/taglib-1.11.1/bin/taglib/ -ltag
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/taglib-1.11.1/bin/taglib/ -ltagd
else:unix: LIBS += -L$$PWD/../lib/taglib-1.11.1/bin/taglib/ -ltag -lz

INCLUDEPATH += $$PWD/../lib/taglib-1.11.1/bin/taglib
DEPENDPATH += $$PWD/../lib/taglib-1.11.1/bin/taglib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/taglib-1.11.1/bin/taglib/libtag.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/taglib-1.11.1/bin/taglib/libtagd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/taglib-1.11.1/bin/taglib/tag.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/taglib-1.11.1/bin/taglib/tagd.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/taglib-1.11.1/bin/taglib/libtag.a
