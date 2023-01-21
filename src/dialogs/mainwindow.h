#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "utils/parameters.h"

#include <QMenu>
#include <QAction>

#include "errorDisplayDialog.h"
#include "aboutDialog.h"
#include "utils/texttospeech.h"

#include "ifaces/IGui.h"
#include <ifaces/IMainWindow.h>

#include<array>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class KeyReceiver;

class MainWindow : public QMainWindow, public IMainWindow
{
    Q_OBJECT

public:
    MainWindow(IGui &face, QWidget *parent = nullptr);
    ~MainWindow();

    void updateGraph(Points *points, double minX, double maxX, double minY, double maxY) override;
    void error(QString errorString) override;
    void updateDerivative(Points *points, double minX, double maxX, double minY, double maxY) override;
    void newCurrentPoint(double x, double y) override;
    void updateLabelText(QString text) override;
    void initialStateActivated() override;
    void evaluateStateActivated() override;
    void graphReadyStateActivated() override;
    void errorDisplayStateActivated() override;
    void playSoundStateActivated() override;
    void playSoundStateDeactivated() override;
    void exploreStateActivated() override;
    void exploreStateDeactivated() override;
    void interestingPointStateActivated() override;
    void interestingPointStateDeactivated() override;
    void interestingPointStoppedStateActivated() override;
    void interestingPointStoppedStateDeactivated() override;
    void newInputValues(double minX, double maxX, double minY, double maxY) override;

protected:
    bool eventFilter(QObject* obj, QEvent* event);

private slots:
    void on_startSoundPushButton_clicked();
    void on_nextPushButton_clicked();
    void on_previousPushButton_clicked();
    void on_nextPointInterestPushButton_clicked();
    void on_previousPointInterestPushButton_clicked();
    void on_xPushButton_clicked();
    void on_yPushButton_clicked();
    void on_previousFastPushButton_clicked();
    void on_nextFastPushButton_clicked();
    void on_firstPointPushButton_clicked();
    void on_lastPointPushButton_clicked();
    void on_minXLineEdit_textEdited(const QString &arg1);
    void on_maxXLineEdit_textEdited(const QString &arg1);
    void on_minYLineEdit_textEdited(const QString &arg1);
    void on_maxYLineEdit_textEdited(const QString &arg1);
    void on_graphColorPushButton_clicked();
    void on_backgroundColorPushButton_clicked();
    void on_highlightColorPushButton_clicked();
    void on_axesColorPushButton_clicked();
    void on_resetGraphSettingsPushButton_clicked();
    void on_resetAudioPushButton_clicked();
    void on_decStepPushButton_clicked();
    void on_incStepPushButton_clicked();
    void on_functionLineEdit_cursorPositionChanged(int arg1, int arg2);
    void on_normalModePushButton_clicked();
    void on_firstDerivativePushButton_clicked();
    void on_secondDerivativePushButton_clicked();
    void durationSpinBoxValueChanged(int value);
    void minFreqSpinBoxValueChanged(int value);
    void maxFreqSpinBoxValueChanged(int value);
    void precisionDigitsSpinboxValueChanged(int value);
    void selfVoiceCheckBoxStateChanged();
    void useNotesCheckBoxStateChanged();
    void useNegativeNotesCheckBoxStateChanged();
    void stopAtZeroCheckBoxStateChanged();
    void graphWidthSpinBoxValueChanged(int value);
    void highlightSizeSpinBoxValueChanged(int value);
    void axesSizeSpinBoxValueChanged(int value);
    void showGridCheckBoxStateChanged();
    void on_derivativeColorPushButton_clicked();
    void sayWidget();
    void updateLabel();
    void openRecentFile();
    void on_derivativePushButton_clicked();
    void on_useNotesCheckBox_toggled(bool checked);
    void on_selfVoiceCheckBox_toggled(bool checked);
    void on_useNegativeNotescheckBox_stateChanged(int arg1);
    void on_stopAtZeroCheckBox_stateChanged(int arg1);
    void initActions();
    void initMenu();
    void setButtonColors();
    void initGraphControls();
    void enableControls();
    void disableControls();
    void focusExpression();
    void clearLabel();
    void stopIntro();
    void newExpression();
    void quit();
    void exit();
    void selfVoiceActionActivated();
    void useNotesActionActivated();
    void useNegativeNotesActionActivated();
    void stopAtZeroActionActivated();
    void incPrecision();
    void decPrecision();
    void errorAccepted();
    void on_functionLineEdit_textEdited(const QString &arg1);
    void performZoom(int delta);
    void mousePressed(int x, int y);
    void mouseMove(int diffX, int diffY);
    void mouseReleased();
    void showShortcuts();
    void showAboutDialog();
    void closeAboutDialog();
    void accessText(QWidget *widget, QString text);
    void readSettings();
    void writeSettings();
    void updateRecentFileActions();

private:

    Ui::MainWindow *ui;
    IGui &iface;
    Points *m_points;
    Points *m_derivPoints;
    double m_minX, m_maxX, m_minY, m_maxY;
    bool m_mousePressed = false;
    int m_xStartDrag, m_yStartDrag;
    double m_minXDrag, m_maxXDrag, m_minYDrag, m_maxYDrag;
    Parameters *m_parameters;
    QAction *newExpressionAction;
    QAction *focusExpressionAction;
    QAction *startSoundButtonAction;
    QAction *nextAction;
    QAction *previousAction;
    QAction *sayXAction;
    QAction *sayYAction;
    QAction *sayDerivativeAction;
    QAction *incStepAction;
    QAction *decStepAction;
    QAction *incPrecisionAction;
    QAction *decPrecisionAction;
    QAction *previousInterestPointAction;
    QAction *nextInterestPointAction;
    QAction *nextFastAction;
    QAction *previousFastAction;
    QAction *firstPointAction;
    QAction *lastPointAction;
    QAction *selfVoiceAction;
    QAction *useNotesAction;
    QAction *useNegativeNotesAction;
    QAction *normalModeAction;
    QAction *firstDerivativeModeAction;
    QAction *secondDerivativeModeAction;
    QAction *showShortcutsAction;
    QAction *aboutAction;
    QAction *introAction;
    QAction *stopAtZeroAction;
    QMenu *helpMenu;
    QMenu *fileMenu;
    QMenu *controlMenu;
    bool canZoomDrag = false;
    KeyReceiver *keyReceiver;
    ErrorDisplayDialog *errorDisplayDialog;
    AboutDialog *aboutDialog;
    QString m_errorString;
    TextToSpeech *m_textToSpeech;
    enum {MaxRecentFiles = 9};
    QStringList recentFiles;
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;
    QAction *exitAction;
    QString helpFile;
};
#endif // MAINWINDOW_H
