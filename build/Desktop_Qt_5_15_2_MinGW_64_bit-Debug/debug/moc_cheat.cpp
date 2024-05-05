/****************************************************************************
** Meta object code from reading C++ file 'cheat.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../cheat.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cheat.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Cheat_t {
    QByteArrayData data[15];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cheat_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cheat_t qt_meta_stringdata_Cheat = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Cheat"
QT_MOC_LITERAL(1, 6, 6), // "change"
QT_MOC_LITERAL(2, 13, 0), // ""
QT_MOC_LITERAL(3, 14, 11), // "slotCheatHp"
QT_MOC_LITERAL(4, 26, 15), // "slotCheatAttack"
QT_MOC_LITERAL(5, 42, 15), // "slotCheatDefend"
QT_MOC_LITERAL(6, 58, 14), // "slotCheatMoney"
QT_MOC_LITERAL(7, 73, 14), // "slotCheatLevel"
QT_MOC_LITERAL(8, 88, 15), // "slotCheatRedKey"
QT_MOC_LITERAL(9, 104, 16), // "slotCheatBlueKey"
QT_MOC_LITERAL(10, 121, 18), // "slotCheatYellowKey"
QT_MOC_LITERAL(11, 140, 13), // "slotCheatBook"
QT_MOC_LITERAL(12, 154, 14), // "slotCheatSword"
QT_MOC_LITERAL(13, 169, 15), // "slotCheatShield"
QT_MOC_LITERAL(14, 185, 13) // "slotCheatMode"

    },
    "Cheat\0change\0\0slotCheatHp\0slotCheatAttack\0"
    "slotCheatDefend\0slotCheatMoney\0"
    "slotCheatLevel\0slotCheatRedKey\0"
    "slotCheatBlueKey\0slotCheatYellowKey\0"
    "slotCheatBook\0slotCheatSword\0"
    "slotCheatShield\0slotCheatMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cheat[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Cheat::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Cheat *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change(); break;
        case 1: _t->slotCheatHp(); break;
        case 2: _t->slotCheatAttack(); break;
        case 3: _t->slotCheatDefend(); break;
        case 4: _t->slotCheatMoney(); break;
        case 5: _t->slotCheatLevel(); break;
        case 6: _t->slotCheatRedKey(); break;
        case 7: _t->slotCheatBlueKey(); break;
        case 8: _t->slotCheatYellowKey(); break;
        case 9: _t->slotCheatBook(); break;
        case 10: _t->slotCheatSword(); break;
        case 11: _t->slotCheatShield(); break;
        case 12: _t->slotCheatMode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Cheat::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cheat::change)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Cheat::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Cheat.data,
    qt_meta_data_Cheat,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Cheat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cheat::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cheat.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Cheat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Cheat::change()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
