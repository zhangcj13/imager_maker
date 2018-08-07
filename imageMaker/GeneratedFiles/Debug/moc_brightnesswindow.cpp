/****************************************************************************
** Meta object code from reading C++ file 'brightnesswindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../brightnesswindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'brightnesswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_brightnessWindow_t {
    QByteArrayData data[10];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_brightnessWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_brightnessWindow_t qt_meta_stringdata_brightnessWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "brightnessWindow"
QT_MOC_LITERAL(1, 17, 24), // "send_Brightness_Contrast"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 19), // "PBrightContrastItem"
QT_MOC_LITERAL(4, 63, 18), // "setValueBrightness"
QT_MOC_LITERAL(5, 82, 16), // "setValueContrast"
QT_MOC_LITERAL(6, 99, 24), // "setSLiderValueBrightness"
QT_MOC_LITERAL(7, 124, 22), // "setSLiderValueContrast"
QT_MOC_LITERAL(8, 147, 8), // "intiData"
QT_MOC_LITERAL(9, 156, 25) // "brightnesswindowTriggered"

    },
    "brightnessWindow\0send_Brightness_Contrast\0"
    "\0PBrightContrastItem\0setValueBrightness\0"
    "setValueContrast\0setSLiderValueBrightness\0"
    "setSLiderValueContrast\0intiData\0"
    "brightnesswindowTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_brightnessWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   54,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       6,    0,   60,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void brightnessWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        brightnessWindow *_t = static_cast<brightnessWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_Brightness_Contrast((*reinterpret_cast< PBrightContrastItem(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->setValueBrightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setValueContrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setSLiderValueBrightness(); break;
        case 4: _t->setSLiderValueContrast(); break;
        case 5: _t->intiData(); break;
        case 6: _t->brightnesswindowTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (brightnessWindow::*_t)(PBrightContrastItem , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&brightnessWindow::send_Brightness_Contrast)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject brightnessWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_brightnessWindow.data,
      qt_meta_data_brightnessWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *brightnessWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *brightnessWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_brightnessWindow.stringdata0))
        return static_cast<void*>(const_cast< brightnessWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int brightnessWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void brightnessWindow::send_Brightness_Contrast(PBrightContrastItem _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
