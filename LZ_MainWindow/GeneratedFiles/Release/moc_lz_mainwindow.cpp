/****************************************************************************
** Meta object code from reading C++ file 'lz_mainwindow.h'
**
** Created: Mon Oct 26 19:05:47 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lz_mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lz_mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LZ_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      61,   15,   14,   14, 0x0a,
     104,   14,   14,   14, 0x0a,
     136,  134,   14,   14, 0x0a,
     172,  160,   14,   14, 0x0a,
     211,   14,   14,   14, 0x0a,
     231,   14,   14,   14, 0x0a,
     252,   14,   14,   14, 0x0a,
     268,   14,   14,   14, 0x0a,
     283,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LZ_MainWindow[] = {
    "LZ_MainWindow\0\0"
    "isPreInHole,isInHole,time_ms,leftDis,rightDis\0"
    "receiveStatus(bool,bool,int,double,double)\0"
    "receiveException(const char*)\0,\0"
    "receiveImg(QImage,bool)\0b0,b1,b2,b3\0"
    "receiveModeChange(bool,bool,bool,bool)\0"
    "onSetInHoleButton()\0onSetOutHoleButton()\0"
    "onActionAbout()\0onActionExit()\0"
    "initCameras()\0"
};

void LZ_MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LZ_MainWindow *_t = static_cast<LZ_MainWindow *>(_o);
        switch (_id) {
        case 0: _t->receiveStatus((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 1: _t->receiveException((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->receiveImg((*reinterpret_cast< const QImage(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->receiveModeChange((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 4: _t->onSetInHoleButton(); break;
        case 5: _t->onSetOutHoleButton(); break;
        case 6: _t->onActionAbout(); break;
        case 7: _t->onActionExit(); break;
        case 8: _t->initCameras(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LZ_MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LZ_MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_LZ_MainWindow,
      qt_meta_data_LZ_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LZ_MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LZ_MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LZ_MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LZ_MainWindow))
        return static_cast<void*>(const_cast< LZ_MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int LZ_MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE