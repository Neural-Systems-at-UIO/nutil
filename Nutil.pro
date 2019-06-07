#QT -= gui
QT += gui  websockets
#CONFIG += static
CONFIG += c++11 console
CONFIG += app_bundle
QT += xml
QT += widgets
QT += core gui
QT += network
TEMPLATE      = app


DEFINES += IS_BETA

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS USE_LIBTIFF
QMAKE_CXXFLAGS += -openmp
QMAKE_CXXFLAGS += -O2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += main.cpp \
    source/util/buffer2d.cpp \
    nutilapplication.cpp \
    mainwindow.cpp \
    node.cpp \
    source/nauto.cpp \
    source/ProcessManager/nutilprocess.cpp \
    source/ProcessManager/processmanager.cpp \
    source/util/limage.cpp \
    source/util/area.cpp \
    source/util/atlaslabel.cpp \
    source/util/flat2d.cpp \
    source/LBook/lbook.cpp \
    source/LBook/lbookxlnt.cpp \
    source/unittest.cpp \
    source/util/shape.cpp \
    source/ProcessManager/report.cpp \
    source/ProcessManager/processitem.cpp \
    source/ProcessManager/processmanagerpcounter.cpp \
    source/ProcessManager/processmanagerfactory.cpp \
    source/ProcessManager/processmanagertransform.cpp \
    source/ProcessManager/processmanagerautocontrast.cpp \
    source/dialogtiff.cpp \
    source/updatethread.cpp \
    source/IO/nifti.cpp \
    source/ProcessManager/areafinder3d.cpp \
    source/IO/pointcloud3d.cpp \
    source/util/nlimagetiff.cpp \
    source/IO/xmlanchor.cpp \
    dialogsettings.cpp \
    source/ProcessManager/processmanagertiffcreator.cpp \
    source/LBook/lbookcsv.cpp

HEADERS += \
    nutilapplication.h \
    source/util/buffer2d.h \
    mainwindow.h \
    node.h \
    source/util/cinifile.h \
    source/nauto.h \
    source/ProcessManager/nutilprocess.h \
    source/ProcessManager/processmanager.h \
    source/util/limage.h \
    source/util/area.h \
    source/util/atlaslabel.h \
    source/util/flat2d.h \
    source/LBook/lbook.h \
    source/LBook/lbookxlnt.h \
    source/unittest.h \
    source/util/shape.h \
    source/ProcessManager/report.h \
    source/ProcessManager/processitem.h \
    source/ProcessManager/processmanagerpcounter.h \
    source/ProcessManager/processmanagerfactory.h \
    source/ProcessManager/processmanagertransform.h \
    source/ProcessManager/processmanagerautocontrast.h \
    source/dialogtiff.h \
    source/updatethread.h \
    source/IO/nifti.h \
    source/ProcessManager/areafinder3d.h \
    source/IO/pointcloud3d.h \
    source/util/nlimagetiff.h \
    source/IO/xmlanchor.h \
    dialogsettings.h \
    source/util/cinifile.h \
    source/ProcessManager/processmanagertiffcreator.h \
    source/LBook/lbookcsv.h

FORMS    += mainwindow.ui \
    source/dialogtiff.ui \
    dialogsettings.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../tiff-4.0.9/libtiff/ -llibtiff
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../tiff-4.0.9/libtiff/ -llibtiffd
#else:unix: LIBS += -L$$PWD/../tiff-4.0.9/libtiff/ -llibtiff

#INCLUDEPATH += $$PWD/../tiff-4.0.9/libtiff
#DEPENDPATH += $$PWD/../tiff-4.0.9/libtiff

unix|win32: LIBS += -L$$PWD/lib/ -llibtiff

INCLUDEPATH += $$PWD/lib/libtiff
INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib/libtiff

LIBS += -L$$PWD/lib/ -lxlnt

#LELIB INCLUDES

 win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LeLib/release/ -llelib
 else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LeLib/debug/ -llelib
 else:symbian: LIBS += -llelib
 else:unix: LIBS += -L$$OUT_PWD/../LeLib/debug/ -llelib

 INCLUDEPATH += $$PWD/../lelib/
 DEPENDPATH += $$PWD/../lelib/

 win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../LeLib/release/lelib.lib
 else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lelib/debug/lelib.lib
 else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../projects/lelib/liblelib.a

#LELIB INCLUDES ENDS

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/libxl-3.8.1.0/lib64/ -llibxl
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/libxl-3.8.1.0/lib64/ -llibxl
#else:unix: LIBS += -L$$PWD/lib/libxl-3.8.1.0/lib64/ -llibxl

#INCLUDEPATH += $$PWD/lib/libxl-3.8.1.0/include_cpp
#DEPENDPATH += $$PWD/lib/libxl-3.8.1.0/include_cpp

DISTFILES +=

RESOURCES += \
    resources.qrc
