TARGET = audiographs

QT       += core gui multimedia texttospeech quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11

QMAKE_CXXFLAGS += -Wa,-mbig-obj

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audionotes/audionotes.cpp \
    audionotes/audiopoints.cpp \
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
    functionController.cpp \
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
    main.cpp \
    utils/parameters.cpp \
    utils/texttospeech.cpp

HEADERS += \
    audionotes/audionotes.h \
    audionotes/audiopoints.h \
    constants.h \
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
    functionController.h \
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
    ifaces/IPointsInterest.h \
    parsers/exprtk/exprtk.hpp \
    utils/parameters.h \
    utils/texttospeech.h
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
    help.qrc

DISTFILES +=

RC_ICONS = audiographs.ico
