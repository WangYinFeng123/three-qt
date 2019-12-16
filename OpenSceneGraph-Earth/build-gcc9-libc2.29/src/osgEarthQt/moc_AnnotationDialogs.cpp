/****************************************************************************
** Meta object code from reading C++ file 'AnnotationDialogs'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/osgEarthQt/AnnotationDialogs"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnnotationDialogs' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_osgEarth__QtGui__BaseAnnotationDialog_t {
    QByteArrayData data[1];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_osgEarth__QtGui__BaseAnnotationDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_osgEarth__QtGui__BaseAnnotationDialog_t qt_meta_stringdata_osgEarth__QtGui__BaseAnnotationDialog = {
    {
QT_MOC_LITERAL(0, 0, 37) // "osgEarth::QtGui::BaseAnnotati..."

    },
    "osgEarth::QtGui::BaseAnnotationDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_osgEarth__QtGui__BaseAnnotationDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void osgEarth::QtGui::BaseAnnotationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject osgEarth::QtGui::BaseAnnotationDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_osgEarth__QtGui__BaseAnnotationDialog.data,
    qt_meta_data_osgEarth__QtGui__BaseAnnotationDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *osgEarth::QtGui::BaseAnnotationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *osgEarth::QtGui::BaseAnnotationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_osgEarth__QtGui__BaseAnnotationDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int osgEarth::QtGui::BaseAnnotationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_osgEarth__QtGui__AddMarkerDialog_t {
    QByteArrayData data[8];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_osgEarth__QtGui__AddMarkerDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_osgEarth__QtGui__AddMarkerDialog_t qt_meta_stringdata_osgEarth__QtGui__AddMarkerDialog = {
    {
QT_MOC_LITERAL(0, 0, 32), // "osgEarth::QtGui::AddMarkerDialog"
QT_MOC_LITERAL(1, 33, 6), // "accept"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 6), // "reject"
QT_MOC_LITERAL(4, 48, 23), // "onNameCheckStateChanged"
QT_MOC_LITERAL(5, 72, 5), // "state"
QT_MOC_LITERAL(6, 78, 17), // "onNameTextChanged"
QT_MOC_LITERAL(7, 96, 4) // "text"

    },
    "osgEarth::QtGui::AddMarkerDialog\0"
    "accept\0\0reject\0onNameCheckStateChanged\0"
    "state\0onNameTextChanged\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_osgEarth__QtGui__AddMarkerDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x08 /* Private */,
       6,    1,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void osgEarth::QtGui::AddMarkerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddMarkerDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->reject(); break;
        case 2: _t->onNameCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onNameTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject osgEarth::QtGui::AddMarkerDialog::staticMetaObject = { {
    &BaseAnnotationDialog::staticMetaObject,
    qt_meta_stringdata_osgEarth__QtGui__AddMarkerDialog.data,
    qt_meta_data_osgEarth__QtGui__AddMarkerDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *osgEarth::QtGui::AddMarkerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *osgEarth::QtGui::AddMarkerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_osgEarth__QtGui__AddMarkerDialog.stringdata0))
        return static_cast<void*>(this);
    return BaseAnnotationDialog::qt_metacast(_clname);
}

int osgEarth::QtGui::AddMarkerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAnnotationDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_osgEarth__QtGui__AddPathDialog_t {
    QByteArrayData data[7];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_osgEarth__QtGui__AddPathDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_osgEarth__QtGui__AddPathDialog_t qt_meta_stringdata_osgEarth__QtGui__AddPathDialog = {
    {
QT_MOC_LITERAL(0, 0, 30), // "osgEarth::QtGui::AddPathDialog"
QT_MOC_LITERAL(1, 31, 6), // "accept"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 6), // "reject"
QT_MOC_LITERAL(4, 46, 24), // "onDrapeCheckStateChanged"
QT_MOC_LITERAL(5, 71, 5), // "state"
QT_MOC_LITERAL(6, 77, 24) // "onLineColorButtonClicked"

    },
    "osgEarth::QtGui::AddPathDialog\0accept\0"
    "\0reject\0onDrapeCheckStateChanged\0state\0"
    "onLineColorButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_osgEarth__QtGui__AddPathDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void osgEarth::QtGui::AddPathDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddPathDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->reject(); break;
        case 2: _t->onDrapeCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onLineColorButtonClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject osgEarth::QtGui::AddPathDialog::staticMetaObject = { {
    &BaseAnnotationDialog::staticMetaObject,
    qt_meta_stringdata_osgEarth__QtGui__AddPathDialog.data,
    qt_meta_data_osgEarth__QtGui__AddPathDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *osgEarth::QtGui::AddPathDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *osgEarth::QtGui::AddPathDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_osgEarth__QtGui__AddPathDialog.stringdata0))
        return static_cast<void*>(this);
    return BaseAnnotationDialog::qt_metacast(_clname);
}

int osgEarth::QtGui::AddPathDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAnnotationDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_osgEarth__QtGui__AddPolygonDialog_t {
    QByteArrayData data[8];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_osgEarth__QtGui__AddPolygonDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_osgEarth__QtGui__AddPolygonDialog_t qt_meta_stringdata_osgEarth__QtGui__AddPolygonDialog = {
    {
QT_MOC_LITERAL(0, 0, 33), // "osgEarth::QtGui::AddPolygonDi..."
QT_MOC_LITERAL(1, 34, 6), // "accept"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 6), // "reject"
QT_MOC_LITERAL(4, 49, 24), // "onDrapeCheckStateChanged"
QT_MOC_LITERAL(5, 74, 5), // "state"
QT_MOC_LITERAL(6, 80, 24), // "onLineColorButtonClicked"
QT_MOC_LITERAL(7, 105, 24) // "onFillColorButtonClicked"

    },
    "osgEarth::QtGui::AddPolygonDialog\0"
    "accept\0\0reject\0onDrapeCheckStateChanged\0"
    "state\0onLineColorButtonClicked\0"
    "onFillColorButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_osgEarth__QtGui__AddPolygonDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void osgEarth::QtGui::AddPolygonDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddPolygonDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->reject(); break;
        case 2: _t->onDrapeCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onLineColorButtonClicked(); break;
        case 4: _t->onFillColorButtonClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject osgEarth::QtGui::AddPolygonDialog::staticMetaObject = { {
    &BaseAnnotationDialog::staticMetaObject,
    qt_meta_stringdata_osgEarth__QtGui__AddPolygonDialog.data,
    qt_meta_data_osgEarth__QtGui__AddPolygonDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *osgEarth::QtGui::AddPolygonDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *osgEarth::QtGui::AddPolygonDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_osgEarth__QtGui__AddPolygonDialog.stringdata0))
        return static_cast<void*>(this);
    return BaseAnnotationDialog::qt_metacast(_clname);
}

int osgEarth::QtGui::AddPolygonDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAnnotationDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_osgEarth__QtGui__AddEllipseDialog_t {
    QByteArrayData data[8];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_osgEarth__QtGui__AddEllipseDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_osgEarth__QtGui__AddEllipseDialog_t qt_meta_stringdata_osgEarth__QtGui__AddEllipseDialog = {
    {
QT_MOC_LITERAL(0, 0, 33), // "osgEarth::QtGui::AddEllipseDi..."
QT_MOC_LITERAL(1, 34, 6), // "accept"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 6), // "reject"
QT_MOC_LITERAL(4, 49, 24), // "onDrapeCheckStateChanged"
QT_MOC_LITERAL(5, 74, 5), // "state"
QT_MOC_LITERAL(6, 80, 24), // "onLineColorButtonClicked"
QT_MOC_LITERAL(7, 105, 24) // "onFillColorButtonClicked"

    },
    "osgEarth::QtGui::AddEllipseDialog\0"
    "accept\0\0reject\0onDrapeCheckStateChanged\0"
    "state\0onLineColorButtonClicked\0"
    "onFillColorButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_osgEarth__QtGui__AddEllipseDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void osgEarth::QtGui::AddEllipseDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddEllipseDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->reject(); break;
        case 2: _t->onDrapeCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onLineColorButtonClicked(); break;
        case 4: _t->onFillColorButtonClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject osgEarth::QtGui::AddEllipseDialog::staticMetaObject = { {
    &BaseAnnotationDialog::staticMetaObject,
    qt_meta_stringdata_osgEarth__QtGui__AddEllipseDialog.data,
    qt_meta_data_osgEarth__QtGui__AddEllipseDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *osgEarth::QtGui::AddEllipseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *osgEarth::QtGui::AddEllipseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_osgEarth__QtGui__AddEllipseDialog.stringdata0))
        return static_cast<void*>(this);
    return BaseAnnotationDialog::qt_metacast(_clname);
}

int osgEarth::QtGui::AddEllipseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseAnnotationDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
