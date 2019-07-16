/****************************************************************************
** Meta object code from reading C++ file 'serverthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TcpServer/serverthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_serverThread_t {
    QByteArrayData data[12];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_serverThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_serverThread_t qt_meta_stringdata_serverThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "serverThread"
QT_MOC_LITERAL(1, 13, 9), // "dataReady"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "isplay"
QT_MOC_LITERAL(4, 31, 8), // "isMaster"
QT_MOC_LITERAL(5, 40, 6), // "weapon"
QT_MOC_LITERAL(6, 47, 6), // "Killhs"
QT_MOC_LITERAL(7, 54, 6), // "Killss"
QT_MOC_LITERAL(8, 61, 6), // "Deaths"
QT_MOC_LITERAL(9, 68, 12), // "recvDataSlot"
QT_MOC_LITERAL(10, 81, 5), // "Kills"
QT_MOC_LITERAL(11, 87, 16) // "disconnectToHost"

    },
    "serverThread\0dataReady\0\0isplay\0isMaster\0"
    "weapon\0Killhs\0Killss\0Deaths\0recvDataSlot\0"
    "Kills\0disconnectToHost"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_serverThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    6,   42,    2, 0x08 /* Private */,
      11,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,   10,    8,
    QMetaType::Void,

       0        // eod
};

void serverThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<serverThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataReady((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 1: _t->recvDataSlot((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 2: _t->disconnectToHost(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (serverThread::*)(bool , bool , int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serverThread::dataReady)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject serverThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_serverThread.data,
    qt_meta_data_serverThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *serverThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *serverThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_serverThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int serverThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void serverThread::dataReady(bool _t1, bool _t2, int _t3, int _t4, int _t5, int _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
