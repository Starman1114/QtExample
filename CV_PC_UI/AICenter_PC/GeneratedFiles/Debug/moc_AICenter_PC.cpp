/****************************************************************************
** Meta object code from reading C++ file 'AICenter_PC.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AICenter_PC.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AICenter_PC.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AICenter_PC_t {
    QByteArrayData data[9];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AICenter_PC_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AICenter_PC_t qt_meta_stringdata_AICenter_PC = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AICenter_PC"
QT_MOC_LITERAL(1, 12, 22), // "on_btnMenu_Min_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 24), // "on_btnMenu_Close_clicked"
QT_MOC_LITERAL(4, 61, 22), // "on_ChooseSpeed_clicked"
QT_MOC_LITERAL(5, 84, 21), // "on_ChooseGame_clicked"
QT_MOC_LITERAL(6, 106, 7), // "addGame"
QT_MOC_LITERAL(7, 114, 3), // "ind"
QT_MOC_LITERAL(8, 118, 10) // "deleteGame"

    },
    "AICenter_PC\0on_btnMenu_Min_clicked\0\0"
    "on_btnMenu_Close_clicked\0"
    "on_ChooseSpeed_clicked\0on_ChooseGame_clicked\0"
    "addGame\0ind\0deleteGame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AICenter_PC[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    1,   48,    2, 0x08 /* Private */,
       8,    1,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int,    7,
    QMetaType::Bool, QMetaType::Int,    7,

       0        // eod
};

void AICenter_PC::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AICenter_PC *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnMenu_Min_clicked(); break;
        case 1: _t->on_btnMenu_Close_clicked(); break;
        case 2: _t->on_ChooseSpeed_clicked(); break;
        case 3: _t->on_ChooseGame_clicked(); break;
        case 4: { bool _r = _t->addGame((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->deleteGame((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AICenter_PC::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_AICenter_PC.data,
    qt_meta_data_AICenter_PC,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AICenter_PC::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AICenter_PC::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AICenter_PC.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int AICenter_PC::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
