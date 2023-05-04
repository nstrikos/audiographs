#ifndef KEYEMITTER_H
#define KEYEMITTER_H

#include <QObject>
#include <QCoreApplication>
#include <QKeyEvent>

class KeyEmitter : public QObject
{
    Q_OBJECT
public:
    KeyEmitter(QObject* parent=nullptr) : QObject(parent) {}
    Q_INVOKABLE void keyTabPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Tab, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyShiftTabPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Tab, Qt::ShiftModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keySpacePressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Space, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyReturnPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Return, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyControlYPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Y, Qt::ControlModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyControlXPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_X, Qt::ControlModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyControlRightPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Right, Qt::ControlModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyControlLeftPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Left, Qt::ControlModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyEndPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_End, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyHomePressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Home, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyF3Pressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_F3, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyF4Pressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_F4, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyF5Pressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_F5, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyUpPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Up, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
    Q_INVOKABLE void keyDownPressed(QObject* tf) {
        QKeyEvent keyPressEvent = QKeyEvent(QEvent::Type::KeyPress, Qt::Key_Down, Qt::NoModifier, "");
        QCoreApplication::sendEvent(tf, &keyPressEvent);
    }
};

#endif // KEYEMITTER_H
