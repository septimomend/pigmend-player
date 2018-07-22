/****************************************************************************
** Meta object code from reading C++ file 'playerControls.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/playerControls.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playerControls.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayerControls_t {
    QByteArrayData data[39];
    char stringdata0[453];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerControls_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerControls_t qt_meta_stringdata_PlayerControls = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PlayerControls"
QT_MOC_LITERAL(1, 15, 16), // "currentMediaItem"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "titleChanged"
QT_MOC_LITERAL(4, 46, 12), // "QStringList*"
QT_MOC_LITERAL(5, 59, 15), // "durationChanged"
QT_MOC_LITERAL(6, 75, 19), // "timeProgressChanged"
QT_MOC_LITERAL(7, 95, 17), // "changeVolumeValue"
QT_MOC_LITERAL(8, 113, 17), // "setVolumeToPlayer"
QT_MOC_LITERAL(9, 131, 4), // "play"
QT_MOC_LITERAL(10, 136, 5), // "pause"
QT_MOC_LITERAL(11, 142, 4), // "stop"
QT_MOC_LITERAL(12, 147, 4), // "next"
QT_MOC_LITERAL(13, 152, 10), // "nextForced"
QT_MOC_LITERAL(14, 163, 4), // "prev"
QT_MOC_LITERAL(15, 168, 12), // "setMediaFile"
QT_MOC_LITERAL(16, 181, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 198, 4), // "item"
QT_MOC_LITERAL(18, 203, 14), // "setVideoWidget"
QT_MOC_LITERAL(19, 218, 12), // "VideoWidget*"
QT_MOC_LITERAL(20, 231, 2), // "vw"
QT_MOC_LITERAL(21, 234, 15), // "setTimeProgress"
QT_MOC_LITERAL(22, 250, 12), // "timeProgress"
QT_MOC_LITERAL(23, 263, 4), // "seek"
QT_MOC_LITERAL(24, 268, 13), // "progressValue"
QT_MOC_LITERAL(25, 282, 11), // "fastForward"
QT_MOC_LITERAL(26, 294, 13), // "setRepeatMode"
QT_MOC_LITERAL(27, 308, 11), // "checkRepeat"
QT_MOC_LITERAL(28, 320, 14), // "setShuffleMode"
QT_MOC_LITERAL(29, 335, 12), // "checkShuffle"
QT_MOC_LITERAL(30, 348, 12), // "setFirstFile"
QT_MOC_LITERAL(31, 361, 9), // "setVolume"
QT_MOC_LITERAL(32, 371, 6), // "volume"
QT_MOC_LITERAL(33, 378, 11), // "setMetaData"
QT_MOC_LITERAL(34, 390, 12), // "processState"
QT_MOC_LITERAL(35, 403, 19), // "QMediaPlayer::State"
QT_MOC_LITERAL(36, 423, 5), // "state"
QT_MOC_LITERAL(37, 429, 14), // "changeDuration"
QT_MOC_LITERAL(38, 444, 8) // "duration"

    },
    "PlayerControls\0currentMediaItem\0\0"
    "titleChanged\0QStringList*\0durationChanged\0"
    "timeProgressChanged\0changeVolumeValue\0"
    "setVolumeToPlayer\0play\0pause\0stop\0"
    "next\0nextForced\0prev\0setMediaFile\0"
    "QListWidgetItem*\0item\0setVideoWidget\0"
    "VideoWidget*\0vw\0setTimeProgress\0"
    "timeProgress\0seek\0progressValue\0"
    "fastForward\0setRepeatMode\0checkRepeat\0"
    "setShuffleMode\0checkShuffle\0setFirstFile\0"
    "setVolume\0volume\0setMetaData\0processState\0"
    "QMediaPlayer::State\0state\0changeDuration\0"
    "duration"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerControls[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  134,    2, 0x06 /* Public */,
       3,    1,  137,    2, 0x06 /* Public */,
       5,    1,  140,    2, 0x06 /* Public */,
       6,    1,  143,    2, 0x06 /* Public */,
       7,    1,  146,    2, 0x06 /* Public */,
       8,    1,  149,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  152,    2, 0x0a /* Public */,
      10,    0,  153,    2, 0x0a /* Public */,
      11,    0,  154,    2, 0x0a /* Public */,
      12,    0,  155,    2, 0x0a /* Public */,
      13,    0,  156,    2, 0x0a /* Public */,
      14,    0,  157,    2, 0x0a /* Public */,
      15,    1,  158,    2, 0x0a /* Public */,
      18,    1,  161,    2, 0x0a /* Public */,
      21,    1,  164,    2, 0x0a /* Public */,
      23,    1,  167,    2, 0x0a /* Public */,
      25,    0,  170,    2, 0x0a /* Public */,
      26,    1,  171,    2, 0x0a /* Public */,
      28,    1,  174,    2, 0x0a /* Public */,
      30,    1,  177,    2, 0x0a /* Public */,
      31,    1,  180,    2, 0x0a /* Public */,
      33,    0,  183,    2, 0x08 /* Private */,
      34,    1,  184,    2, 0x08 /* Private */,
      37,    1,  187,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::LongLong,   22,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   27,
    QMetaType::Void, QMetaType::Bool,   29,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 35,   36,
    QMetaType::Void, QMetaType::LongLong,   38,

       0        // eod
};

void PlayerControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayerControls *_t = static_cast<PlayerControls *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentMediaItem((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->titleChanged((*reinterpret_cast< QStringList*(*)>(_a[1]))); break;
        case 2: _t->durationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->timeProgressChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeVolumeValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->setVolumeToPlayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->play(); break;
        case 7: _t->pause(); break;
        case 8: _t->stop(); break;
        case 9: _t->next(); break;
        case 10: _t->nextForced(); break;
        case 11: _t->prev(); break;
        case 12: _t->setMediaFile((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 13: _t->setVideoWidget((*reinterpret_cast< VideoWidget*(*)>(_a[1]))); break;
        case 14: _t->setTimeProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 15: _t->seek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->fastForward(); break;
        case 17: _t->setRepeatMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->setShuffleMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->setFirstFile((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 20: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->setMetaData(); break;
        case 22: _t->processState((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        case 23: _t->changeDuration((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VideoWidget* >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PlayerControls::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::currentMediaItem)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)(QStringList * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::titleChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::durationChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::timeProgressChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::changeVolumeValue)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PlayerControls::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerControls::setVolumeToPlayer)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlayerControls::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayerControls.data,
      qt_meta_data_PlayerControls,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlayerControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerControls::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerControls.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlayerControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void PlayerControls::currentMediaItem(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayerControls::titleChanged(QStringList * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayerControls::durationChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayerControls::timeProgressChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayerControls::changeVolumeValue(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PlayerControls::setVolumeToPlayer(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
