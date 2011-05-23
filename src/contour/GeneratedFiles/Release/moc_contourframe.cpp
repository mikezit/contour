/****************************************************************************
** Meta object code from reading C++ file 'contourframe.h'
**
** Created: Fri May 15 11:19:01 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../contourframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contourframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ContourFrame[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      31,   13,   13,   13, 0x0a,
      51,   13,   13,   13, 0x0a,
      65,   13,   13,   13, 0x0a,
      79,   13,   13,   13, 0x0a,
      94,   13,   13,   13, 0x0a,
     109,   13,   13,   13, 0x0a,
     129,  125,   13,   13, 0x0a,
     147,   13,   13,   13, 0x0a,
     169,  162,   13,   13, 0x0a,
     205,  196,   13,   13, 0x0a,
     233,  224,   13,   13, 0x0a,
     257,  247,   13,   13, 0x0a,
     276,   13,   13,   13, 0x08,
     292,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ContourFrame[] = {
    "ContourFrame\0\0importGridFile()\0"
    "importScatterFile()\0randContour()\0"
    "setRandInfo()\0saveRandData()\0"
    "saveGridData()\0setTraceValue()\0i,j\0"
    "setLabel(int,int)\0editColorMap()\0"
    "colors\0newColorMap(QList<QColor>)\0"
    "isFillOn\0setFillColor(bool)\0isGridOn\0"
    "setGrid(bool)\0isPointOn\0setPointShow(bool)\0"
    "setHorizonBar()\0setVerticalBar()\0"
};

const QMetaObject ContourFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ContourFrame,
      qt_meta_data_ContourFrame, 0 }
};

const QMetaObject *ContourFrame::metaObject() const
{
    return &staticMetaObject;
}

void *ContourFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ContourFrame))
        return static_cast<void*>(const_cast< ContourFrame*>(this));
    if (!strcmp(_clname, "Ui::CFrame"))
        return static_cast< Ui::CFrame*>(const_cast< ContourFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int ContourFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: importGridFile(); break;
        case 1: importScatterFile(); break;
        case 2: randContour(); break;
        case 3: setRandInfo(); break;
        case 4: saveRandData(); break;
        case 5: saveGridData(); break;
        case 6: setTraceValue(); break;
        case 7: setLabel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: editColorMap(); break;
        case 9: newColorMap((*reinterpret_cast< QList<QColor>(*)>(_a[1]))); break;
        case 10: setFillColor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: setGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: setPointShow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: setHorizonBar(); break;
        case 14: setVerticalBar(); break;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
