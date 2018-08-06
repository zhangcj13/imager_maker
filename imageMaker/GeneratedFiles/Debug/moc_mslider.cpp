/****************************************************************************
** Meta object code from reading C++ file 'mslider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mslider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mslider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_mSlider_t {
    QByteArrayData data[15];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mSlider_t qt_meta_stringdata_mSlider = {
    {
QT_MOC_LITERAL(0, 0, 7), // "mSlider"
QT_MOC_LITERAL(1, 8, 15), // "minValueChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "maxValueChanged"
QT_MOC_LITERAL(4, 41, 18), // "factorValueChanged"
QT_MOC_LITERAL(5, 60, 8), // "setLabel"
QT_MOC_LITERAL(6, 69, 5), // "label"
QT_MOC_LITERAL(7, 75, 11), // "setMaxValue"
QT_MOC_LITERAL(8, 87, 3), // "val"
QT_MOC_LITERAL(9, 91, 11), // "setMinValue"
QT_MOC_LITERAL(10, 103, 14), // "setFactorValue"
QT_MOC_LITERAL(11, 118, 15), // "refreshAllValue"
QT_MOC_LITERAL(12, 134, 5), // "_val1"
QT_MOC_LITERAL(13, 140, 5), // "_val2"
QT_MOC_LITERAL(14, 146, 5) // "_val3"

    },
    "mSlider\0minValueChanged\0\0maxValueChanged\0"
    "factorValueChanged\0setLabel\0label\0"
    "setMaxValue\0val\0setMinValue\0setFactorValue\0"
    "refreshAllValue\0_val1\0_val2\0_val3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    1,   57,    2, 0x06 /* Public */,
       4,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   63,    2, 0x0a /* Public */,
       7,    1,   66,    2, 0x0a /* Public */,
       9,    1,   69,    2, 0x0a /* Public */,
      10,    1,   72,    2, 0x0a /* Public */,
      11,    3,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,   12,   13,   14,

       0        // eod
};

void mSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mSlider *_t = static_cast<mSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->minValueChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->maxValueChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->factorValueChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->setLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setMaxValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->setMinValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->setFactorValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->refreshAllValue((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (mSlider::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mSlider::minValueChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (mSlider::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mSlider::maxValueChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (mSlider::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mSlider::factorValueChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject mSlider::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mSlider.data,
      qt_meta_data_mSlider,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mSlider.stringdata0))
        return static_cast<void*>(const_cast< mSlider*>(this));
    return QWidget::qt_metacast(_clname);
}

int mSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void mSlider::minValueChanged(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mSlider::maxValueChanged(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mSlider::factorValueChanged(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
