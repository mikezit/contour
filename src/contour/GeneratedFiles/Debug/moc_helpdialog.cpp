/****************************************************************************
** Meta object code from reading C++ file 'helpdialog.h'
**
** Created: Fri May 15 09:31:12 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dialog/helpdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'helpdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HelpDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HelpDialog[] = {
    "HelpDialog\0\0showHtml()\0"
};

const QMetaObject HelpDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_HelpDialog,
      qt_meta_data_HelpDialog, 0 }
};

const QMetaObject *HelpDialog::metaObject() const
{
    return &staticMetaObject;
}

void *HelpDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HelpDialog))
        return static_cast<void*>(const_cast< HelpDialog*>(this));
    if (!strcmp(_clname, "Ui::HelpDialog"))
        return static_cast< Ui::HelpDialog*>(const_cast< HelpDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int HelpDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showHtml(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
