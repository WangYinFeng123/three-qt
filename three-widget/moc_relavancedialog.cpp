/****************************************************************************
** Meta object code from reading C++ file 'relavancedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "three-d-widget/form/relavancedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'relavancedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RelavanceDialog_t {
    QByteArrayData data[15];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RelavanceDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RelavanceDialog_t qt_meta_stringdata_RelavanceDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "RelavanceDialog"
QT_MOC_LITERAL(1, 16, 10), // "requestOid"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "oldOid"
QT_MOC_LITERAL(4, 35, 8), // "QString&"
QT_MOC_LITERAL(5, 44, 6), // "newOid"
QT_MOC_LITERAL(6, 51, 11), // "description"
QT_MOC_LITERAL(7, 63, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(8, 85, 26), // "on_tableWidget_cellChanged"
QT_MOC_LITERAL(9, 112, 3), // "row"
QT_MOC_LITERAL(10, 116, 6), // "column"
QT_MOC_LITERAL(11, 123, 26), // "on_tableWidget_cellClicked"
QT_MOC_LITERAL(12, 150, 31), // "on_listWidget_itemDoubleClicked"
QT_MOC_LITERAL(13, 182, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(14, 199, 4) // "item"

    },
    "RelavanceDialog\0requestOid\0\0oldOid\0"
    "QString&\0newOid\0description\0"
    "on_buttonBox_accepted\0on_tableWidget_cellChanged\0"
    "row\0column\0on_tableWidget_cellClicked\0"
    "on_listWidget_itemDoubleClicked\0"
    "QListWidgetItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RelavanceDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   46,    2, 0x08 /* Private */,
       8,    2,   47,    2, 0x08 /* Private */,
      11,    2,   52,    2, 0x08 /* Private */,
      12,    1,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4, 0x80000000 | 4,    3,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void RelavanceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RelavanceDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestOid((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->on_buttonBox_accepted(); break;
        case 2: _t->on_tableWidget_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->on_tableWidget_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_listWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RelavanceDialog::*)(QString , QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RelavanceDialog::requestOid)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RelavanceDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_RelavanceDialog.data,
    qt_meta_data_RelavanceDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RelavanceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RelavanceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RelavanceDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int RelavanceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void RelavanceDialog::requestOid(QString _t1, QString & _t2, QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE