/****************************************************************************
** Meta object code from reading C++ file 'blackwhiltethreshwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../blackwhiltethreshwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'blackwhiltethreshwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_blackwhilteThreshWindow_t {
    QByteArrayData data[7];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_blackwhilteThreshWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_blackwhilteThreshWindow_t qt_meta_stringdata_blackwhilteThreshWindow = {
    {
QT_MOC_LITERAL(0, 0, 23), // "blackwhilteThreshWindow"
QT_MOC_LITERAL(1, 24, 13), // "ThreshChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 8), // "intiData"
QT_MOC_LITERAL(4, 48, 23), // "text2slider_refleshData"
QT_MOC_LITERAL(5, 72, 23), // "slider2text_refleshData"
QT_MOC_LITERAL(6, 96, 32) // "blackwhilteThreshWindowTriggered"

    },
    "blackwhilteThreshWindow\0ThreshChanged\0"
    "\0intiData\0text2slider_refleshData\0"
    "slider2text_refleshData\0"
    "blackwhilteThreshWindowTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_blackwhilteThreshWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   44,    2, 0x08 /* Private */,
       4,    0,   45,    2, 0x08 /* Private */,
       5,    1,   46,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void blackwhilteThreshWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        blackwhilteThreshWindow *_t = static_cast<blackwhilteThreshWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ThreshChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->intiData(); break;
        case 2: _t->text2slider_refleshData(); break;
        case 3: _t->slider2text_refleshData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->blackwhilteThreshWindowTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (blackwhilteThreshWindow::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&blackwhilteThreshWindow::ThreshChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject blackwhilteThreshWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_blackwhilteThreshWindow.data,
      qt_meta_data_blackwhilteThreshWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *blackwhilteThreshWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *blackwhilteThreshWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_blackwhilteThreshWindow.stringdata0))
        return static_cast<void*>(const_cast< blackwhilteThreshWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int blackwhilteThreshWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void blackwhilteThreshWindow::ThreshChanged(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
