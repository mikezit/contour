/****************************************************************************
** Meta object code from reading C++ file 'contourview.h'
**
** Created: Fri May 15 09:31:13 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../contourview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contourview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ContourView[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      36,   13,   12,   12, 0x05,
      76,   13,   12,   12, 0x05,
     120,  116,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ContourView[] = {
    "ContourView\0\0min,max,baseSize,scale\0"
    "setVCoordinate(float,float,float,float)\0"
    "setHCoordinate(float,float,float,float)\0"
    "x,y\0indexChanged(int,int)\0"
};

const QMetaObject ContourView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_ContourView,
      qt_meta_data_ContourView, 0 }
};

const QMetaObject *ContourView::metaObject() const
{
    return &staticMetaObject;
}

void *ContourView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ContourView))
        return static_cast<void*>(const_cast< ContourView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int ContourView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setVCoordinate((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 1: setHCoordinate((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 2: indexChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ContourView::setVCoordinate(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ContourView::setHCoordinate(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ContourView::indexChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
