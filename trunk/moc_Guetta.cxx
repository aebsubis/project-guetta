/****************************************************************************
** Meta object code from reading C++ file 'Guetta.h'
**
** Created: Tue Nov 1 17:56:24 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Guetta.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Guetta.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Guetta[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x0a,
      36,    8,    7,    7, 0x0a,
      77,   58,    7,    7, 0x0a,
     103,    7,    7,    7, 0x0a,
     126,    7,    7,    7, 0x0a,
     142,    7,    7,    7, 0x0a,
     159,    7,    7,    7, 0x0a,
     176,    7,    7,    7, 0x0a,
     200,    7,    7,    7, 0x0a,
     219,    7,    7,    7, 0x0a,
     251,  240,    7,    7, 0x0a,
     274,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Guetta[] = {
    "Guetta\0\0cloud\0changeCloud1(QString)\0"
    "changeCloud2(QString)\0idPoint,idViewport\0"
    "selectedKeyPoint(int,int)\0"
    "changeKeyPointMethod()\0changeOptions()\0"
    "changeAcumular()\0procesarClouds()\0"
    "seleccionarDirectorio()\0seleccionarTodos()\0"
    "deseleccionarTodos()\0incremento\0"
    "cambiarIncremento(int)\0changeShowKeypoints()\0"
};

const QMetaObject Guetta::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Guetta,
      qt_meta_data_Guetta, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Guetta::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Guetta::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Guetta::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Guetta))
        return static_cast<void*>(const_cast< Guetta*>(this));
    return QDialog::qt_metacast(_clname);
}

int Guetta::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeCloud1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: changeCloud2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: selectedKeyPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: changeKeyPointMethod(); break;
        case 4: changeOptions(); break;
        case 5: changeAcumular(); break;
        case 6: procesarClouds(); break;
        case 7: seleccionarDirectorio(); break;
        case 8: seleccionarTodos(); break;
        case 9: deseleccionarTodos(); break;
        case 10: cambiarIncremento((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: changeShowKeypoints(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
