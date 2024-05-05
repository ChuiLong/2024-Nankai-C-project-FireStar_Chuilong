/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_View_t {
    QByteArrayData data[11];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_View_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_View_t qt_meta_stringdata_View = {
    {
QT_MOC_LITERAL(0, 0, 4), // "View"
QT_MOC_LITERAL(1, 5, 4), // "move"
QT_MOC_LITERAL(2, 10, 0), // ""
QT_MOC_LITERAL(3, 11, 1), // "x"
QT_MOC_LITERAL(4, 13, 1), // "y"
QT_MOC_LITERAL(5, 15, 6), // "events"
QT_MOC_LITERAL(6, 22, 3), // "str"
QT_MOC_LITERAL(7, 26, 5), // "fight"
QT_MOC_LITERAL(8, 32, 3), // "num"
QT_MOC_LITERAL(9, 36, 6), // "change"
QT_MOC_LITERAL(10, 43, 4) // "quit"

    },
    "View\0move\0\0x\0y\0events\0str\0fight\0num\0"
    "change\0quit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_View[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    1,   44,    2, 0x06 /* Public */,
       7,    1,   47,    2, 0x06 /* Public */,
       9,    0,   50,    2, 0x06 /* Public */,
      10,    0,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<View *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->events((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->fight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->change(); break;
        case 4: _t->quit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (View::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::move)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (View::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::events)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (View::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::fight)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (View::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::change)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (View::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&View::quit)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject View::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_View.data,
    qt_meta_data_View,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_View.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void View::move(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void View::events(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void View::fight(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void View::change()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void View::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
