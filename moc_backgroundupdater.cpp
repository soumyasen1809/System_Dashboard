/****************************************************************************
** Meta object code from reading C++ file 'backgroundupdater.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "backgroundupdater.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backgroundupdater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BackgroundUpdater_t {
    QByteArrayData data[8];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BackgroundUpdater_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BackgroundUpdater_t qt_meta_stringdata_BackgroundUpdater = {
    {
QT_MOC_LITERAL(0, 0, 17), // "BackgroundUpdater"
QT_MOC_LITERAL(1, 18, 34), // "on_checkBox_mem_usage_stateCh..."
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 4), // "arg1"
QT_MOC_LITERAL(4, 59, 34), // "on_checkBox_net_stats_stateCh..."
QT_MOC_LITERAL(5, 94, 33), // "on_pushButton_refresh_all_cli..."
QT_MOC_LITERAL(6, 128, 33), // "on_checkBox_cpu_temp_stateCha..."
QT_MOC_LITERAL(7, 162, 7) // "refresh"

    },
    "BackgroundUpdater\0on_checkBox_mem_usage_stateChanged\0"
    "\0arg1\0on_checkBox_net_stats_stateChanged\0"
    "on_pushButton_refresh_all_clicked\0"
    "on_checkBox_cpu_temp_stateChanged\0"
    "refresh"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackgroundUpdater[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       5,    0,   45,    2, 0x0a /* Public */,
       6,    1,   46,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void BackgroundUpdater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackgroundUpdater *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_checkBox_mem_usage_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_checkBox_net_stats_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_refresh_all_clicked(); break;
        case 3: _t->on_checkBox_cpu_temp_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->refresh(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BackgroundUpdater::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BackgroundUpdater.data,
    qt_meta_data_BackgroundUpdater,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BackgroundUpdater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackgroundUpdater::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BackgroundUpdater.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BackgroundUpdater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
