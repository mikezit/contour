/****************************************************************************
** Meta object code from reading C++ file 'colormapedit.h'
**
** Created: Fri May 15 09:31:15 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dialog/colormapedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'colormapedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ColormapEdit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      21,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   49,   13,   13, 0x08,
      63,   49,   13,   13, 0x08,
      73,   49,   13,   13, 0x08,
      87,   13,   13,   13, 0x08,
      98,   13,   13,   13, 0x08,
     110,   13,   13,   13, 0x08,
     125,   13,   13,   13, 0x08,
     137,   13,   13,   13, 0x08,
     151,   13,   13,   13, 0x08,
     166,   13,   13,   13, 0x08,
     189,  183,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ColormapEdit[] = {
    "ColormapEdit\0\0colors\0newColorList(QList<QColor>)\0"
    "n\0rotate(int)\0bias(int)\0contrast(int)\0"
    "setColor()\0okPressed()\0applyPressed()\0"
    "biasReset()\0rotateReset()\0contrastRest()\0"
    "updateColormap()\0index\0resetMap(int)\0"
};

const QMetaObject ColormapEdit::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ColormapEdit,
      qt_meta_data_ColormapEdit, 0 }
};

const QMetaObject *ColormapEdit::metaObject() const
{
    return &staticMetaObject;
}

void *ColormapEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColormapEdit))
        return static_cast<void*>(const_cast< ColormapEdit*>(this));
    if (!strcmp(_clname, "Ui::colormapEdit"))
        return static_cast< Ui::colormapEdit*>(const_cast< ColormapEdit*>(this));
    return QDialog::qt_metacast(_clname);
}

int ColormapEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newColorList((*reinterpret_cast< QList<QColor>(*)>(_a[1]))); break;
        case 1: rotate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: bias((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: contrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setColor(); break;
        case 5: okPressed(); break;
        case 6: applyPressed(); break;
        case 7: biasReset(); break;
        case 8: rotateReset(); break;
        case 9: contrastRest(); break;
        case 10: updateColormap(); break;
        case 11: resetMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ColormapEdit::newColorList(QList<QColor> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
