#ifndef IGUI_H
#define IGUI_H

class MainWindow;
class QString;

class IGui
{
public:
    virtual void addGui(MainWindow *gui) = 0;
    virtual void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY) = 0;
    virtual void startDrag(int x , int y) = 0;
    virtual void drag(int diffX, int diffY, int width, int height) = 0;
    virtual void zoom(double delta) = 0;
    virtual void playSound() = 0;
    virtual void stopSound() = 0;
    virtual void nextPoint() = 0;
    virtual void previousPoint() = 0;
    virtual void previousPointInterest() = 0;
    virtual void nextPointInterest() = 0;
    virtual void setDerivativeMode(int mode) = 0;
    virtual void sayX() = 0;
    virtual void sayY() = 0;
    virtual void getX() = 0;
    virtual void getY() = 0;
    virtual void incStep() = 0;
    virtual void decStep() = 0;
    virtual void previousFast() = 0;
    virtual void nextFast() = 0;
    virtual void firstPoint() = 0;
    virtual void lastPoint() = 0;
    virtual void stopAtZeroChanged() = 0;
    virtual void sayDerivative() = 0;
    virtual void getDerivative() = 0;
    virtual void evaluate() = 0;
    virtual void newGraph() = 0;
    virtual void functionError() = 0;
    virtual void playPressed() = 0;
    virtual void errorAccepted() = 0;
};

#endif // IGUI_H
