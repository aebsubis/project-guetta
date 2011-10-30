/****************************************************************************
** Meta object code from reading C++ file 'newForm.h'
**
** Created: Sun Oct 9 18:38:15 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "newForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_newForm[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      58,   53,   17,    8, 0x0a,
     103,   97,   74,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_newForm[] = {
    "newForm\0\0click()\0pcl::PointCloud<pcl::PointXYZ>::Ptr\0"
    "name\0loadPCD(string)\0vector<GuettaKeyPoint>\0"
    "cloud\0getGuettaCloud(PointCloud<PointXYZ>::Ptr)\0"
};

const QMetaObject newForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_newForm,
      qt_meta_data_newForm, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &newForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *newForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *newForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_newForm))
        return static_cast<void*>(const_cast< newForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int newForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: click(); break;
        case 1: { pcl::PointCloud<pcl::PointXYZ>::Ptr _r = loadPCD((*reinterpret_cast< string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< pcl::PointCloud<pcl::PointXYZ>::Ptr*>(_a[0]) = _r; }  break;
        case 2: { vector<GuettaKeyPoint> _r = getGuettaCloud((*reinterpret_cast< PointCloud<PointXYZ>::Ptr(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< vector<GuettaKeyPoint>*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
