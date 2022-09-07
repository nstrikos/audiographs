#include "dialogs/mainwindow.h"

#include <QApplication>
#include "functionController.h"
#include "function/functionModel.h"
#include "function/dragHandler.h"
#include "function/functionZoomer.h"
#include "function/currentPoint.h"
#include "generator/audio.h"
#include "audionotes/audionotes.h"
#include "function/pointsInterest.h"

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);

        FunctionController *controller = new FunctionController();
        MainWindow *w = new MainWindow(*controller);
        FunctionModel *model = new FunctionModel(*controller);
        DragHandler *dragHandler = new DragHandler(*controller, *model);
        FunctionZoomer *zoomer = new FunctionZoomer(*controller, *model);
        CurrentPoint *currentPoint = new CurrentPoint(*controller, *model);
        Audio *audio = new Audio(*controller);
        AudioNotes *audionotes = new AudioNotes(*controller, *model);
        PointsInterest *pointsInterest = new PointsInterest(*controller, *model, *audionotes, *currentPoint);

        w->showMaximized();

        int ret = a.exec();

        delete w;
        delete model;
        delete dragHandler;
        delete zoomer;
        delete currentPoint;
        delete audio;
        delete pointsInterest;
        delete audionotes;
        delete controller;

        return ret;
}
