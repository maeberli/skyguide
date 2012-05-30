/****************************************************************************
** Meta object code from reading C++ file 'skycomponent.h'
**
** Created: Wed 23. May 11:48:01 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SkyGuide/src/skycomponent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skycomponent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SkyComponent[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,   13,   13,   13, 0x0a,
      81,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SkyComponent[] = {
    "SkyComponent\0\0type,message\0"
    "logMessage(SKYLOGGER::SkyLoggerTypes,QString)\0"
    "start()\0stop()\0"
};

const QMetaObject SkyComponent::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SkyComponent,
      qt_meta_data_SkyComponent, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SkyComponent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SkyComponent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SkyComponent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkyComponent))
        return static_cast<void*>(const_cast< SkyComponent*>(this));
    return QObject::qt_metacast(_clname);
}

int SkyComponent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: logMessage((*reinterpret_cast< SKYLOGGER::SkyLoggerTypes(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: start(); break;
        case 2: stop(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SkyComponent::logMessage(SKYLOGGER::SkyLoggerTypes _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
