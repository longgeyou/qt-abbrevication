/****************************************************************************
** Meta object code from reading C++ file 'abbreviation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Abbreviation/abbreviation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abbreviation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Abbreviation_t {
    QByteArrayData data[14];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Abbreviation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Abbreviation_t qt_meta_stringdata_Abbreviation = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Abbreviation"
QT_MOC_LITERAL(1, 13, 18), // "slot_addButtonTest"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 9), // "slot_test"
QT_MOC_LITERAL(4, 43, 13), // "slot_textShow"
QT_MOC_LITERAL(5, 57, 11), // "slot_search"
QT_MOC_LITERAL(6, 69, 25), // "slot_abbreButtonOnClicked"
QT_MOC_LITERAL(7, 95, 3), // "num"
QT_MOC_LITERAL(8, 99, 11), // "slot_dirSet"
QT_MOC_LITERAL(9, 111, 15), // "slot_fileBrowse"
QT_MOC_LITERAL(10, 127, 17), // "slot_dialogAccept"
QT_MOC_LITERAL(11, 145, 17), // "slot_dialogReject"
QT_MOC_LITERAL(12, 163, 16), // "slot_dialogApply"
QT_MOC_LITERAL(13, 180, 16) // "slot_fileProTest"

    },
    "Abbreviation\0slot_addButtonTest\0\0"
    "slot_test\0slot_textShow\0slot_search\0"
    "slot_abbreButtonOnClicked\0num\0slot_dirSet\0"
    "slot_fileBrowse\0slot_dialogAccept\0"
    "slot_dialogReject\0slot_dialogApply\0"
    "slot_fileProTest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Abbreviation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    1,   73,    2, 0x0a /* Public */,
       8,    0,   76,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x0a /* Public */,
      12,    0,   80,    2, 0x0a /* Public */,
      13,    0,   81,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Abbreviation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Abbreviation *_t = static_cast<Abbreviation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_addButtonTest(); break;
        case 1: _t->slot_test(); break;
        case 2: _t->slot_textShow(); break;
        case 3: _t->slot_search(); break;
        case 4: _t->slot_abbreButtonOnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_dirSet(); break;
        case 6: _t->slot_fileBrowse(); break;
        case 7: _t->slot_dialogAccept(); break;
        case 8: _t->slot_dialogReject(); break;
        case 9: _t->slot_dialogApply(); break;
        case 10: _t->slot_fileProTest(); break;
        default: ;
        }
    }
}

const QMetaObject Abbreviation::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Abbreviation.data,
      qt_meta_data_Abbreviation,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Abbreviation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Abbreviation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Abbreviation.stringdata0))
        return static_cast<void*>(const_cast< Abbreviation*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Abbreviation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
