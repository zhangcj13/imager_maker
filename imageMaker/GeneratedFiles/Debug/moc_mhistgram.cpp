/****************************************************************************
** Meta object code from reading C++ file 'mhistgram.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mhistgram.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mhistgram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_mHistGram_t {
    QByteArrayData data[7];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mHistGram_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mHistGram_t qt_meta_stringdata_mHistGram = {
    {
QT_MOC_LITERAL(0, 0, 9), // "mHistGram"
QT_MOC_LITERAL(1, 10, 15), // "setHisShowModel"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "data"
QT_MOC_LITERAL(4, 32, 16), // "resetMaxHistgram"
QT_MOC_LITERAL(5, 49, 16), // "resetMinHistgram"
QT_MOC_LITERAL(6, 66, 19) // "resetFactorHistgram"

    },
    "mHistGram\0setHisShowModel\0\0data\0"
    "resetMaxHistgram\0resetMinHistgram\0"
    "resetFactorHistgram"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mHistGram[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       5,    1,   40,    2, 0x08 /* Private */,
       6,    1,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,

       0        // eod
};

void mHistGram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mHistGram *_t = static_cast<mHistGram *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setHisShowModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->resetMaxHistgram((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->resetMinHistgram((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->resetFactorHistgram((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject mHistGram::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mHistGram.data,
      qt_meta_data_mHistGram,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mHistGram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mHistGram::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mHistGram.stringdata0))
        return static_cast<void*>(const_cast< mHistGram*>(this));
    return QWidget::qt_metacast(_clname);
}

int mHistGram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
