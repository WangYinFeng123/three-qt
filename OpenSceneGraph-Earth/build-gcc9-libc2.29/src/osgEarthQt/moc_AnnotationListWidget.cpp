/****************************************************************************
** Meta object code from reading C++ file 'AnnotationListWidget'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/osgEarthQt/AnnotationListWidget"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnnotationListWidget' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_osgEarth__QtGui__AnnotationListWidget_t {
    QByteArrayData data[13];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_osgEarth__QtGui__AnnotationListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_osgEarth__QtGui__AnnotationListWidget_t qt_meta_stringdata_osgEarth__QtGui__AnnotationListWidget = {
    {
QT_MOC_LITERAL(0, 0, 37), // "osgEarth::QtGui::AnnotationLi..."
QT_MOC_LITERAL(1, 38, 12), // "onMapChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 18), // "onSelectionChanged"
QT_MOC_LITERAL(4, 71, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(5, 91, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(6, 108, 4), // "item"
QT_MOC_LITERAL(7, 113, 13), // "onItemChanged"
QT_MOC_LITERAL(8, 127, 22), // "onListSelectionChanged"
QT_MOC_LITERAL(9, 150, 16), // "onRemoveSelected"
QT_MOC_LITERAL(10, 167, 14), // "onEditSelected"
QT_MOC_LITERAL(11, 182, 13), // "onAddFinished"
QT_MOC_LITERAL(12, 196, 6) // "result"

    },
    "osgEarth::QtGui::AnnotationListWidget\0"
    "onMapChanged\0\0onSelectionChanged\0"
    "onItemDoubleClicked\0QListWidgetItem*\0"
    "item\0onItemChanged\0onListSelectionChanged\0"
    "onRemoveSelected\0onEditSelected\0"
    "onAddFinished\0result"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_osgEarth__QtGui__AnnotationListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    1,   56,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,
      10,    0,   64,    2, 0x08 /* Private */,
      11,    1,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void osgEarth::QtGui::AnnotationListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AnnotationListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onMapChanged(); break;
        case 1: _t->onSelectionChanged(); break;
        case 2: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->onItemChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->onListSelectionChanged(); break;
        case 5: _t->onRemoveSelected(); break;
        case 6: _t->onEditSelected(); break;
        case 7: _t->onAddFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject osgEarth::QtGui::AnnotationListWidget::staticMetaObject = { {
    &CollapsiblePairWidget::staticMetaObject,
    qt_meta_stringdata_osgEarth__QtGui__AnnotationListWidget.data,
    qt_meta_data_osgEarth__QtGui__AnnotationListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *osgEarth::QtGui::AnnotationListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *osgEarth::QtGui::AnnotationListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_osgEarth__QtGui__AnnotationListWidget.stringdata0))
        return static_cast<void*>(this);
    return CollapsiblePairWidget::qt_metacast(_clname);
}

int osgEarth::QtGui::AnnotationListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CollapsiblePairWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
