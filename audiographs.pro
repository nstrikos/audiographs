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

HEADERS       = audiooutput.h \
    AndroidClient.h \
                audioengine.h \
    atmsp.h \
    audiopoints.h \
    #functiondomainparser.h \
    generator.h \
    generator/genfunctioncalculator.h \
    generator/genclipper.h \
    generator/genmaxfinder.h \
    generator/genminfinder.h \
    generator/genmod.h \
    generator/genmodvalues.h \
    generator/genparameters.h \
    generator/genphicalculator.h \
    generator/gensum.h \
    parameters.h \
    fparser/fparser_gmpint.hh \
    fparser/fparser_mpfr.hh \
    fparser/fparser.hh \
    fparser/fpconfig.hh \
    fparser/extrasrc/fpaux.hh \
    fparser/extrasrc/fptypes.hh \
    function.h      \
    test.h \
    texttospeech.h


SOURCES       = main.cpp \
    AndroidClient.cpp \
    audiopoints.cpp \
    audiooutput.cpp \
    audioengine.cpp \
    #functiondomainparser.cpp \
    generator.cpp \
    generator/genfunctioncalculator.cpp \
    generator/genclipper.cpp \
    generator/genmaxfinder.cpp \
    generator/genminfinder.cpp \
    generator/genmod.cpp \
    generator/genmodvalues.cpp \
    generator/genparameters.cpp \
    generator/genphicalculator.cpp \
    generator/gensum.cpp \
    parameters.cpp \
    fparser/fparser.cc \
    fparser/fpoptimizer.cc \
    function.cpp \
    test.cpp \
    texttospeech.cpp

unix:!android {
    HEADERS +=  appwindow.h \
                graphsettingsdialog.h \
                renderarea.h \



    SOURCES +=  appwindow.cpp \
                graphsettingsdialog.cpp \
                renderarea.cpp \
}

FORMS += \
    appwindow.ui \
    graphsettingsdialog.ui

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    fparser/extrasrc/fp_opcode_add.inc \
    fparser/extrasrc/fp_identifier_parser.inc

RESOURCES += \
    qml.qrc

contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
