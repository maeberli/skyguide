/****************************************************************************
** Meta object code from reading C++ file 'skygui.h'
**
** Created: Wed 23. May 11:48:03 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SkyGuide/src/skygui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skygui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SkyGui[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      25,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,    7,    7,    7, 0x0a,
      49,    7,    7,    7, 0x0a,
      64,   56,    7,    7, 0x0a,
      85,   56,    7,    7, 0x0a,
     104,   56,    7,    7, 0x0a,
     131,  122,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SkyGui[] = {
    "SkyGui\0\0startAffichage()\0stopAffichage()\0"
    "start()\0stop()\0message\0showWarning(QString)\0"
    "showError(QString)\0showInfo(QString)\0"
    "elements\0updateAffichage(QList<SkyGuiElement*>)\0"
};

const QMetaObject SkyGui::staticMetaObject = {
    { &SkyComponent::staticMetaObject, qt_meta_stringdata_SkyGui,
      qt_meta_data_SkyGui, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SkyGui::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SkyGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SkyGui::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SkyGui))
        return static_cast<void*>(const_cast< SkyGui*>(this));
    return SkyComponent::qt_metacast(_clname);
}

int SkyGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SkyComponent::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: startAffichage(); break;
        case 1: stopAffichage(); break;
        case 2: start(); break;
        case 3: stop(); break;
        case 4: showWarning((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: showError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: showInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: updateAffichage((*reinterpret_cast< const QList<SkyGuiElement*>(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SkyGui::startAffichage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SkyGui::stopAffichage()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
