#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "audioengine.h"
#include "renderarea.h"
#include "graphsettingsdialog.h"
#include "audiopoints.h"
#include "function.h"
#include <QKeyEvent>
#include <QSettings>
#include <QScreen>

namespace Ui {
class AppWindow;
}

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget *parent = nullptr);
    ~AppWindow();

    void setFunction(Function *function);

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void draw();

signals:
    void calcPoints(FunctionInput);

private slots:
    void drawButtonClicked();
    void error(QString text);

    //To check
    void startButtonClicked();
    void stopButtonClicked();
    void on_actionGraph_settings_triggered();

private:
    void keyPressEvent(QKeyEvent *ev);
    Ui::AppWindow *ui;
    AudioEngine *audioEngine;
    void resetAudioEngine();
    Parameters *m_parameters;
    GraphSettingsDialog *graphSettingsDialog;
    QVector<double> *m_xValues;
    QVector<double> *m_yValues;
    double m_yMin;
    double m_yMax;
    int m_curPoint;
    void nextPoint();
    void previousPoint();
    void setAudioPointsFreq();
    void saveSettings();
    void readSettings();
    void initVariables();
    void initUi();
    void connectSignals();
    AudioPoints *m_audioPoints;
    Function *m_function;
};

#endif // APPWINDOW_H
