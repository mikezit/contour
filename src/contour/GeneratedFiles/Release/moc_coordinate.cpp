/****************************************************************************
** Meta object code from reading C++ file 'coordinate.h'
**
** Created: Fri May 15 11:18:59 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../coordinate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coordinate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Coordinate[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      35,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Coordinate[] = {
    "Coordinate\0\0min,max,baseSize,scale\0"
    "addjust(float,float,float,float)\0"
};

const QMetaObject Coordinate::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_Coordinate,
      qt_meta_data_Coordinate, 0 }
};

const QMetaObject *Coordinate::metaObject() const
{
    return &staticMetaObject;
}

void *Coordinate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Coordinate))
        return static_cast<void*>(const_cast< Coordinate*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int Coordinate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addjust((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
