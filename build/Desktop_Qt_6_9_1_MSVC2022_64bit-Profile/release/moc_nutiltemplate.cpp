/****************************************************************************
** Meta object code from reading C++ file 'nutiltemplate.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../source/IO/nutiltemplate.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nutiltemplate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN17NutilTemplateItemE_t {};
} // unnamed namespace

template <> constexpr inline auto NutilTemplateItem::qt_create_metaobjectdata<qt_meta_tag_ZN17NutilTemplateItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NutilTemplateItem",
        "Type",
        "STRING",
        "LIST",
        "DIRECTORY",
        "FILE",
        "TEXTFIELD",
        "NUMBER",
        "NONE",
        "COLOR",
        "MATRIXFIELD"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Type'
        QtMocHelpers::EnumData<Type>(1, 1, QMC::EnumFlags{}).add({
            {    2, Type::STRING },
            {    3, Type::LIST },
            {    4, Type::DIRECTORY },
            {    5, Type::FILE },
            {    6, Type::TEXTFIELD },
            {    7, Type::NUMBER },
            {    8, Type::NONE },
            {    9, Type::COLOR },
            {   10, Type::MATRIXFIELD },
        }),
    };
    return QtMocHelpers::metaObjectData<NutilTemplateItem, qt_meta_tag_ZN17NutilTemplateItemE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NutilTemplateItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17NutilTemplateItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17NutilTemplateItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17NutilTemplateItemE_t>.metaTypes,
    nullptr
} };

void NutilTemplateItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NutilTemplateItem *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *NutilTemplateItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NutilTemplateItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17NutilTemplateItemE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NutilTemplateItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN13NutilTemplateE_t {};
} // unnamed namespace

template <> constexpr inline auto NutilTemplate::qt_create_metaobjectdata<qt_meta_tag_ZN13NutilTemplateE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NutilTemplate",
        "emitUpdate",
        "",
        "emitRePopulate"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'emitUpdate'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'emitRePopulate'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NutilTemplate, qt_meta_tag_ZN13NutilTemplateE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NutilTemplate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13NutilTemplateE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13NutilTemplateE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13NutilTemplateE_t>.metaTypes,
    nullptr
} };

void NutilTemplate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NutilTemplate *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->emitUpdate(); break;
        case 1: _t->emitRePopulate(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NutilTemplate::*)()>(_a, &NutilTemplate::emitUpdate, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NutilTemplate::*)()>(_a, &NutilTemplate::emitRePopulate, 1))
            return;
    }
}

const QMetaObject *NutilTemplate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NutilTemplate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13NutilTemplateE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NutilTemplate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void NutilTemplate::emitUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NutilTemplate::emitRePopulate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
