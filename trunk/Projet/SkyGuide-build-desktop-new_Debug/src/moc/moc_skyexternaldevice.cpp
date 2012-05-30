/****************************************************************************
** Meta object code from reading C++ file 'skyexternaldevice.h'
**
** Created: Wed 23. May 11:48:03 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SkyGuide/src/skyexternaldevice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skyexternaldevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SkyExternalDevice[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   19,   18,   18, 0x05,
      82,   72,   18,   18, 0x05,
     122,  109,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     148,   18,   18,   18, 0x0a,
     156,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SkyExternalDevice[] = {
    "SkyExternalDevice\0\0slope,inclLeftRight\0"
    "receivedOrientationData(int,int)\0"
    "direction\0receivedDirectionData(int)\0"
    "positionData\0receivedPositionData(int)\0"
    "start()\0stop()\0"
};

const QMetaObject SkyExternalDevice::staticMetaObject = {
    { &SkyComponent::staticMetaObject, qt_meta_stringdata_SkyExternalDevice,
      qt_meta_data_SkyExternalDevice, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SkyExternalDevice::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SkyExternalDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SkyExternalDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkyExternalDevice))
        return static_cast<void*>(const_cast< SkyExternalDevice*>(this));
    return SkyComponent::qt_metacast(_clname);
}

int SkyExternalDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SkyComponent::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: receivedOrientationData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: receivedDirectionData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: receivedPositionData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: start(); break;
        case 4: stop(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SkyExternalDevice::receivedOrientationData(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SkyExternalDevice::receivedDirectionData(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SkyExternalDevice::receivedPositionData(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
