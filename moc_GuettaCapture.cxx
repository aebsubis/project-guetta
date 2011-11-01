/****************************************************************************
** Meta object code from reading C++ file 'GuettaCapture.h'
**
** Created: Tue Nov 1 18:22:19 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GuettaCapture.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GuettaCapture.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GuettaCapture[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   15,   14,   14, 0x0a,
      60,   14,   14,   14, 0x0a,
      83,   14,   14,   14, 0x0a,
      99,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GuettaCapture[] = {
    "GuettaCapture\0\0idPoint,idViewport\0"
    "selectedKeyPoint(int,int)\0"
    "connectOpenNIGrabber()\0renameCapture()\0"
    "capture()\0"
};

const QMetaObject GuettaCapture::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GuettaCapture,
      qt_meta_data_GuettaCapture, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GuettaCapture::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GuettaCapture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GuettaCapture::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GuettaCapture))
        return static_cast<void*>(const_cast< GuettaCapture*>(this));
    return QDialog::qt_metacast(_clname);
}

int GuettaCapture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selectedKeyPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: connectOpenNIGrabber(); break;
        case 2: renameCapture(); break;
        case 3: capture(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
