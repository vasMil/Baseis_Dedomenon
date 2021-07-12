/****************************************************************************
** Meta object code from reading C++ file 'evaluatormain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../gui_evaluation/evaluator/evaluatormain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'evaluatormain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EvaluatorMain_t {
    QByteArrayData data[19];
    char stringdata0[410];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EvaluatorMain_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EvaluatorMain_t qt_meta_stringdata_EvaluatorMain = {
    {
QT_MOC_LITERAL(0, 0, 13), // "EvaluatorMain"
QT_MOC_LITERAL(1, 14, 26), // "on_actionLog_Out_triggered"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(4, 66, 22), // "on_but_profile_clicked"
QT_MOC_LITERAL(5, 89, 22), // "on_but_profile_pressed"
QT_MOC_LITERAL(6, 112, 23), // "on_but_profile_released"
QT_MOC_LITERAL(7, 136, 19), // "on_but_jobs_clicked"
QT_MOC_LITERAL(8, 156, 19), // "on_but_jobs_pressed"
QT_MOC_LITERAL(9, 176, 20), // "on_but_jobs_released"
QT_MOC_LITERAL(10, 197, 22), // "on_but_myJobs_released"
QT_MOC_LITERAL(11, 220, 21), // "on_but_myJobs_clicked"
QT_MOC_LITERAL(12, 242, 21), // "on_but_myJobs_pressed"
QT_MOC_LITERAL(13, 264, 22), // "on_but_results_pressed"
QT_MOC_LITERAL(14, 287, 23), // "on_but_results_released"
QT_MOC_LITERAL(15, 311, 22), // "on_but_results_clicked"
QT_MOC_LITERAL(16, 334, 24), // "on_but_myResults_pressed"
QT_MOC_LITERAL(17, 359, 25), // "on_but_myResults_released"
QT_MOC_LITERAL(18, 385, 24) // "on_but_myResults_clicked"

    },
    "EvaluatorMain\0on_actionLog_Out_triggered\0"
    "\0on_actionExit_triggered\0"
    "on_but_profile_clicked\0on_but_profile_pressed\0"
    "on_but_profile_released\0on_but_jobs_clicked\0"
    "on_but_jobs_pressed\0on_but_jobs_released\0"
    "on_but_myJobs_released\0on_but_myJobs_clicked\0"
    "on_but_myJobs_pressed\0on_but_results_pressed\0"
    "on_but_results_released\0on_but_results_clicked\0"
    "on_but_myResults_pressed\0"
    "on_but_myResults_released\0"
    "on_but_myResults_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EvaluatorMain[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EvaluatorMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EvaluatorMain *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionLog_Out_triggered(); break;
        case 1: _t->on_actionExit_triggered(); break;
        case 2: _t->on_but_profile_clicked(); break;
        case 3: _t->on_but_profile_pressed(); break;
        case 4: _t->on_but_profile_released(); break;
        case 5: _t->on_but_jobs_clicked(); break;
        case 6: _t->on_but_jobs_pressed(); break;
        case 7: _t->on_but_jobs_released(); break;
        case 8: _t->on_but_myJobs_released(); break;
        case 9: _t->on_but_myJobs_clicked(); break;
        case 10: _t->on_but_myJobs_pressed(); break;
        case 11: _t->on_but_results_pressed(); break;
        case 12: _t->on_but_results_released(); break;
        case 13: _t->on_but_results_clicked(); break;
        case 14: _t->on_but_myResults_pressed(); break;
        case 15: _t->on_but_myResults_released(); break;
        case 16: _t->on_but_myResults_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject EvaluatorMain::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_EvaluatorMain.data,
    qt_meta_data_EvaluatorMain,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EvaluatorMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EvaluatorMain::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EvaluatorMain.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int EvaluatorMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
