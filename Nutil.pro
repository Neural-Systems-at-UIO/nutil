#QT -= gui
QT += gui
QT += xml
#websockets
#CONFIG += static
CONFIG += c++11 c++17 c++14 console
CONFIG += app_bundle

QT += widgets
QT += core gui
QT += network
ARCH = $$QMAKE_HOST.arch
#ARCH = arm64
TEMPLATE      = app
QTPLUGIN += qtiff

#DEFINES += IS_BETA IGNORE_DOWNLOAD
DEFINES += IGNORE_DOWNLOAD



win32:RC_ICONS += nutil_logo.ico
ICON = nutil_logo.png


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to cewxQQQ3                                                                                                                                                 know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS USE_LIBTIFF #NO_OMP

win32-msvc*{
    QMAKE_CXXFLAGS += -openmp -Zc:twoPhase-
#    QT_LIBS += -lQtXml

}


macx {
    LIBS += -lomp

QMAKE_CXXFLAGS += -Xpreprocessor -fopenmp -I/usr/local/include
QMAKE_CXXFLAGS += -Ofast

    contains(ARCH, x86_64) |contains(ARCH, amd64): {

        INCLUDEPATH += /usr/local/include/
        LIBS += -L/usr/local/lib/
        LIBS += -ltiff

        LIBS += -L$$PWD/lib/    -lxlnt #LIBS += -L/usr/local/opt/libomp/lib -lomp

        LIBS += -L/usr/local/lib /usr/local/lib/libomp.dylib -lomp
    }

#    QMAKE_CXXFLAGS += -Ofast

    contains(ARCH, arm64): {
        message("Arme meg!")
        CONFIG += arm64
        # OMP
#        QMAKE_CXXFLAGS += -Xpreprocessor -fopenmp
        # TIFF
        INCLUDEPATH += /usr/local/include/
        LIBS += -L/usr/local/lib/
        LIBS += -ltiff
        # XLNT
        LIBS += -L$$PWD/lib/   $$PWD/lib/libxlnt-arm.dylib


        # OMP
        QMAKE_CXXFLAGS+= -I/opt/homebrew/opt/libomp/include
        LIBS+= -L/opt/homebrew/opt/libomp/lib
        # libomp 13
        #QMAKE_CXXFLAGS+= -I/opt/homebrew/opt/libomp/include
        #LIBS+= -L/opt/homebrew/opt/libomp/lib
        #LIBS += -lomp


    }
    contains(ARCH, x86_64) |contains(ARCH, amd64):  {
        QMAKE_CXXFLAGS+= -I/usr/local/opt/libomp/include

   }

}


QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_RELEASE += -O2
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += main.cpp \
    source/IO/nutiltemplate.cpp \
    source/LBook/lbookhtml.cpp \
    source/ProcessManager/processmanagerneuroglancer.cpp \
    source/ProcessManager/processmanagerng.cpp \
    source/ProcessManager/processmanagerresize.cpp \
    source/ProcessManager/processmanagervolumiser.cpp \
    source/Validator/nutilvalidator.cpp \
    source/data.cpp \
    source/dialoggeneratedata.cpp \
    source/dialoghelp.cpp \
    source/dialognewfile.cpp \
    source/limage/lcolorlist.cpp \
    source/limage/limage.cpp \
    source/limage/limageqimage.cpp \
    source/limage/limagetiff.cpp \
    source/ltiff/ltiff.cpp \
    source/util/buffer2d.cpp \
    nutilapplication.cpp \
    mainwindow.cpp \
    node.cpp \
    source/nauto.cpp \
    source/ProcessManager/nutilprocess.cpp \
    source/ProcessManager/processmanager.cpp \
    source/util/coordinatetransform.cpp \
    source/util/downloadmanager.cpp \
    source/util/lgraph.cpp \
    source/util/area.cpp \
    source/util/atlaslabel.cpp \
    source/util/flat2d.cpp \
    source/LBook/lbook.cpp \
    source/LBook/lbookxlnt.cpp \
    source/unittest.cpp \
    source/util/neuroglancer.cpp \
    source/util/nlimage.cpp \
    source/util/lmessage.cpp \
    source/util/lparameter.cpp \
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
    source/LBook/lbookcsv.cpp \
    source/LBook/lbookfactory.cpp \
    source/util/slasher.cpp \
    source/util/spline.cpp \
    source/util/updater.cpp \
    source/util/util.cpp \
    source/util/SimplexNoise.cpp

HEADERS += \
    nutilapplication.h \
    source/IO/nutiltemplate.h \
    source/LBook/lbookhtml.h \
    source/ProcessManager/processmanagerneuroglancer.h \
    source/ProcessManager/processmanagerng.h \
    source/ProcessManager/processmanagerresize.h \
    source/ProcessManager/processmanagervolumiser.h \
    source/Validator/nutilvalidator.h \
    source/data.h \
    source/dialoggeneratedata.h \
    source/dialoghelp.h \
    source/dialognewfile.h \
    source/limage/lcolorlist.h \
    source/limage/limage.h \
    source/limage/limageqimage.h \
    source/limage/limagetiff.h \
    source/ltiff/ltiff.h \
    source/util/buffer2d.h \
    mainwindow.h \
    node.h \
    source/util/cinifile.h \
    source/nauto.h \
    source/ProcessManager/nutilprocess.h \
    source/ProcessManager/processmanager.h \
    source/util/coordinatetransform.h \
    source/util/counter.h \
    source/util/downloadmanager.h \
    source/util/lgraph.h \
    source/util/area.h \
    source/util/atlaslabel.h \
    source/util/flat2d.h \
    source/LBook/lbook.h \
    source/LBook/lbookxlnt.h \
    source/unittest.h \
    source/util/neuroglancer.h \
    source/util/nlimage.h \
    source/util/lmessage.h \
    source/util/lparameter.h \
    source/util/random.h \
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
    source/LBook/lbookcsv.h \
    source/LBook/lbookfactory.h \
    source/util/slasher.h \
    source/util/spline.h \
    source/util/updater.h \
    source/util/util.h \
    source/util/SimplexNoise.h

FORMS    += mainwindow.ui \
    source/dialoggeneratedata.ui \
    source/dialoghelp.ui \
    source/dialognewfile.ui \
    source/dialogtiff.ui \
    dialogsettings.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../tiff-4.0.9/libtiff/ -llibtiff
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../tiff-4.0.9/libtiff/ -llibtiffd
#else:unix: LIBS += -L$$PWD/../tiff-4.0.9/libtiff/ -llibtiff

#INCLUDEPATH += $$PWD/../tiff-4.0.9/libtiff
#DEPENDPATH += $$PWD/../tiff-4.0.9/libtiff


win32-msvc*{

    unix|win32: LIBS += -L$$PWD/lib/ -llibtiff

    INCLUDEPATH += $$PWD/lib/libtiff
    INCLUDEPATH += $$PWD/lib
    DEPENDPATH += $$PWD/lib/libtiff

#    LIBS += -L$$PWD/lib/ -lxlnt

    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lxlnt
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/Debug/ -lxlntd

}


linux*{

    LIBS += -ltiff

    INCLUDEPATH += $$PWD/lib/libtiff
    INCLUDEPATH += $$PWD/lib/
    DEPENDPATH += $$PWD/lib/libtiff

    LIBS += -L$$PWD/lib/ -lxlnt
}

#LELIB INCLUDES

# win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LeLib/release/ -llelib
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LeLib/debug/ -llelib
# else:symbian: LIBS += -llelib
 #else:unix: LIBS += -L$$OUT_PWD/../LeLib/Release/ -lLeLib

# INCLUDEPATH += $$PWD/../lelib/
# DEPENDPATH += $$PWD/../lelib/

# win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lelib/release/lelib.lib
# else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lelib/debug/lelib.lib


linux*{
    QMAKE_CXXFLAGS += -fopenmp
    QMAKE_CXXFLAGS +=  -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare -Wno-comment -Wno-parentheses -Wno-delete-non-virtual-dtor -Wno-missing-noreturn
    LIBS += -fopenmp
    QMAKE_CXXFLAGS +=  -Ofast
#    LIBS += -L$$PWD/libs/lua/ -llua -ldl

#    linux:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lelib/Release/
 #   linux:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lelib/Debug/



#    LIBS += -L$$OUT_PWD/../../lelib/Release/ -lLeLib
#    LIBS += -L$$OUT_PWD/../../lelib/Debug/ -lLeLib
#    LIBS += -lLeLib


}

# else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../LeLib/Release/libLeLib.a

#LELIB INCLUDES ENDS

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/libxl-3.8.1.0/lib64/ -llibxl
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/libxl-3.8.1.0/lib64/ -llibxl
#else:unix: LIBS += -L$$PWD/lib/libxl-3.8.1.0/lib64/ -llibxl

#INCLUDEPATH += $$PWD/lib/libxl-3.8.1.0/include_cpp
#DEPENDPATH += $$PWD/lib/libxl-3.8.1.0/include_cpp

DISTFILES += \
    Resources/Nutil_logo_black.png \
    Resources/text/quantifier.txt \
    Resources/text/tiffcreator.txt

RESOURCES += \
    resources.qrc
