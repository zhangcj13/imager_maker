/****************************************************************************
** Meta object code from reading C++ file 'chromawindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../chromawindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chromawindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_chromaWindow_t {
    QByteArrayData data[11];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_chromaWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_chromaWindow_t qt_meta_stringdata_chromaWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "chromaWindow"
QT_MOC_LITERAL(1, 13, 14), // "PHLSItemChange"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "PHLSItem"
QT_MOC_LITERAL(4, 38, 9), // "setValueH"
QT_MOC_LITERAL(5, 48, 9), // "setValueS"
QT_MOC_LITERAL(6, 58, 9), // "setValueL"
QT_MOC_LITERAL(7, 68, 15), // "setSLiderValueH"
QT_MOC_LITERAL(8, 84, 15), // "setSLiderValueS"
QT_MOC_LITERAL(9, 100, 15), // "setSLiderValueL"
QT_MOC_LITERAL(10, 116, 21) // "chromaWindowTriggered"

    },
    "chromaWindow\0PHLSItemChange\0\0PHLSItem\0"
    "setValueH\0setValueS\0setValueL\0"
    "setSLiderValueH\0setSLiderValueS\0"
    "setSLiderValueL\0chromaWindowTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chromaWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   59,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       6,    1,   65,    2, 0x08 /* Private */,
       7,    0,   68,    2, 0x08 /* Private */,
       8,    0,   69,    2, 0x08 /* Private */,
       9,    0,   70,    2, 0x08 /* Private */,
      10,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void chromaWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        chromaWindow *_t = static_cast<chromaWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->PHLSItemChange((*reinterpret_cast< PHLSItem(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->setValueH((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setValueS((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setValueL((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setSLiderValueH(); break;
        case 5: _t->setSLiderValueS(); break;
        case 6: _t->setSLiderValueL(); break;
        case 7: _t->chromaWindowTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (chromaWindow::*_t)(PHLSItem , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&chromaWindow::PHLSItemChange)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject chromaWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_chromaWindow.data,
      qt_meta_data_chromaWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *chromaWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chromaWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_chromaWindow.stringdata0))
        return static_cast<void*>(const_cast< chromaWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int chromaWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void chromaWindow::PHLSItemChange(PHLSItem _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
