TEMPLATE = app
TARGET = audiographs

QT += multimedia texttospeech

CONFIG += c++11

unix:!android {
QT += widgets quick
}

android: {
QT += core gui quick androidextras
}

HEADERS       = \
    AndroidClient.h \
    atmsp.h \
    audioengine.h \
    audionotes.h \
    audiooutput.h \
    audiopoints.h \
    constants.h \
    curve.h \
    curveinterface.h \
    curvemovingpoint.h \
    fparser/fparser.hh \
    fparser/fparser_gmpint.hh \
    fparser/fparser_mpfr.hh \
    fparser/fpconfig.hh \
    function.h \
    generator.h \
    generator/genclipper.h \
    generator/genfunctioncalculator.h \
    generator/genmaxfinder.h \
    generator/genminfinder.h \
    generator/genmod.h \
    generator/genmodvalues.h \
    generator/genparameters.h \
    generator/genphicalculator.h \
    generator/gensum.h \
    parameters.h \
    point.h \
    test.h \
    texttospeech.h
    #functiondomainparser.h \


SOURCES       = \
    AndroidClient.cpp \
    audioengine.cpp \
    audionotes.cpp \
    audiooutput.cpp \
    audiopoints.cpp \
    curve.cpp \
    curveinterface.cpp \
    curvemovingpoint.cpp \
    fparser/fparser.cc \
    fparser/fpoptimizer.cc \
    function.cpp \
    generator.cpp \
    generator/genclipper.cpp \
    generator/genfunctioncalculator.cpp \
    generator/genmaxfinder.cpp \
    generator/genminfinder.cpp \
    generator/genmod.cpp \
    generator/genmodvalues.cpp \
    generator/genparameters.cpp \
    generator/genphicalculator.cpp \
    generator/gensum.cpp \
    main.cpp \
    parameters.cpp \
    point.cpp \
    test.cpp \
    texttospeech.cpp
    #functiondomainparser.cpp \

#unix:!android {
#    HEADERS +=  \
#    appwindow.h \
#    graphsettingsdialog.h \
#    renderarea.h \

#    SOURCES +=  \
#    appwindow.cpp \
#    graphsettingsdialog.cpp \
#    renderarea.cpp \
#}

#FORMS += \
#    appwindow.ui \
#    graphsettingsdialog.ui

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/src/org/nstrikos/access/audiographs/AndroidClient.java \
    fparser/extrasrc/fp_opcode_add.inc \
    fparser/extrasrc/fp_identifier_parser.inc

RESOURCES += \
    qml.qrc

contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
