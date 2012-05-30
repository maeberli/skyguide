/****************************************************************************
** Meta object code from reading C++ file 'skycore.h'
**
** Created: Wed 23. May 11:47:59 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SkyGuide/src/skycore.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skycore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SkyCore[] = {

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
      17,    8,    8,    8, 0x0a,
      67,   24,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SkyCore[] = {
    "SkyCore\0\0start()\0stop()\0"
    "slope,inclLeftRight,direction,positionData\0"
    "calculateRange(int,int,int,int)\0"
};

const QMetaObject SkyCore::staticMetaObject = {
    { &SkyComponent::staticMetaObject, qt_meta_stringdata_SkyCore,
      qt_meta_data_SkyCore, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SkyCore::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SkyCore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SkyCore::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkyCore))
        return static_cast<void*>(const_cast< SkyCore*>(this));
    return SkyComponent::qt_metacast(_clname);
}

int SkyCore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SkyComponent::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: start(); break;
        case 1: stop(); break;
        case 2: calculateRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
