/****************************************************************************
** Meta object code from reading C++ file 'skyextdevdatahandler.h'
**
** Created: Wed 23. May 11:48:04 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SkyGuide/src/skyextdevdatahandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skyextdevdatahandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SkyExtDevDataHandler[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      65,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     122,  102,   21,   21, 0x0a,
     160,  150,   21,   21, 0x0a,
     195,  182,   21,   21, 0x0a,
     216,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SkyExtDevDataHandler[] = {
    "SkyExtDevDataHandler\0\0"
    "slope,inclLeftRight,direction,positionData\0"
    "newExtDataAvailable(int,int,int,int)\0"
    "slope,inclLeftRight\0setOrientationData(int,int)\0"
    "direction\0setDirectionData(int)\0"
    "positionData\0setPositionData(int)\0"
    "timerTimeout()\0"
};

const QMetaObject SkyExtDevDataHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SkyExtDevDataHandler,
      qt_meta_data_SkyExtDevDataHandler, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SkyExtDevDataHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SkyExtDevDataHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SkyExtDevDataHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkyExtDevDataHandler))
        return static_cast<void*>(const_cast< SkyExtDevDataHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int SkyExtDevDataHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newExtDataAvailable((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: setOrientationData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: setDirectionData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setPositionData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: timerTimeout(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SkyExtDevDataHandler::newExtDataAvailable(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
