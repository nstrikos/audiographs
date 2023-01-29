TARGET = audiographs

QT += core gui multimedia texttospeech quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32: {
QMAKE_CXXFLAGS += -Wa,-mbig-obj
#QMAKE_CXXFLAGS += -bigobj
}

SOURCES += \
    audionotes/audionotes.cpp \
    audionotes/audiopoints.cpp \
    controller/functionController.cpp \
    controller/stateMachine.cpp \
    dialogs/aboutDialog.cpp \
    dialogs/errorDisplayDialog.cpp \
    dialogs/mainwindow.cpp \
    dialogs/renderArea.cpp \
    function/currentPoint.cpp \
    function/dragHandler.cpp \
    function/functionDescription.cpp \
    function/functionModel.cpp \
    function/functionZoomer.cpp \
    function/point.cpp \
    function/pointsInterest.cpp \
    generator/audio.cpp \
    generator/audioengine.cpp \
    generator/genclipper.cpp \
    generator/generator.cpp \
    generator/genfunctioncalculator.cpp \
    generator/genmaxfinder.cpp \
    generator/genminfinder.cpp \
    generator/genmod.cpp \
    generator/genmodvalues.cpp \
    generator/genparameters.cpp \
    generator/genphicalculator.cpp \
    generator/gensum.cpp \
    ifaces/IMainWindow.cpp \
    main.cpp \
    mobileview/functionDisplayView.cpp \
    mobileview/functionDisplayViewInterface.cpp \
    mobileview/functionPointView.cpp \
    mobileview/qmlConnector.cpp \
    utils/parameters.cpp \
    utils/texttospeech.cpp \
    utils/util.cpp

HEADERS += \
    audionotes/audionotes.h \
    audionotes/audiopoints.h \
    controller/functionController.h \
    controller/stateMachine.h \
    dialogs/aboutDialog.h \
    dialogs/errorDisplayDialog.h \
    dialogs/mainwindow.h \
    dialogs/renderArea.h \
    function/currentPoint.h \
    function/dragHandler.h \
    function/functionDescription.h \
    function/functionModel.h \
    function/functionZoomer.h \
    function/point.h \
    function/pointsInterest.h \
    generator/audio.h \
    generator/audioengine.h \
    generator/genclipper.h \
    generator/generator.h \
    generator/genfunctioncalculator.h \
    generator/genmaxfinder.h \
    generator/genminfinder.h \
    generator/genmod.h \
    generator/genmodvalues.h \
    generator/genparameters.h \
    generator/genphicalculator.h \
    generator/gensum.h \
    ifaces/IAudio.h \
    ifaces/IAudioNotes.h \
    ifaces/ICurrentPoint.h \
    ifaces/IDragZoom.h \
    ifaces/IFunctionModel.h \
    ifaces/IGui.h \
    ifaces/IMainWindow.h \
    ifaces/IPointsInterest.h \
    ifaces/IStateMachine.h \
    mobileview/functionDisplayView.h \
    mobileview/functionDisplayViewInterface.h \
    mobileview/functionPointView.h \
    mobileview/qmlConnector.h \
    parsers/exprtk/exprtk.hpp \
    utils/constants.h \
    utils/parameters.h \
    utils/texttospeech.h \
    utils/util.h
    parsers/exprtk/exprtk.hpp


FORMS += \
    dialogs/aboutDialog.ui \
    dialogs/errorDisplayDialog.ui \
    dialogs/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    help.qrc \
    translations.qrc
    qml.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

TRANSLATIONS += translations/audiographs_el_GR.ts

RC_ICONS = audiographs.ico

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
