/****************************************************************************
** Meta object code from reading C++ file 'tracesetdialog.h'
**
** Created: Fri May 15 11:18:57 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dialog/tracesetdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tracesetdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TraceDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      24,   12,   12,   12, 0x08,
      38,   12,   12,   12, 0x08,
      54,   12,   12,   12, 0x08,
      66,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TraceDialog[] = {
    "TraceDialog\0\0addValue()\0removeValue()\0"
    "cleanAllValue()\0toDefault()\0getList()\0"
};

const QMetaObject TraceDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TraceDialog,
      qt_meta_data_TraceDialog, 0 }
};

const QMetaObject *TraceDialog::metaObject() const
{
    return &staticMetaObject;
}

void *TraceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TraceDialog))
        return static_cast<void*>(const_cast< TraceDialog*>(this));
    if (!strcmp(_clname, "Ui::TracingDialog"))
        return static_cast< Ui::TracingDialog*>(const_cast< TraceDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TraceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addValue(); break;
        case 1: removeValue(); break;
        case 2: cleanAllValue(); break;
        case 3: toDefault(); break;
        case 4: getList(); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
