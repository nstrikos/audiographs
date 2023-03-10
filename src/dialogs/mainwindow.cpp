#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "math.h"

#include <QDebug>
#include <QColorDialog>
#include <QKeyEvent>
#include <QSpinBox>
#include <QDesktopServices>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(IGui &iface, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      iface(iface)
{
    ui->setupUi(this);
    iface.addGui(this);
    m_textToSpeech = &TextToSpeech::getInstance();
    m_parameters = &Parameters::getInstance();
    ui->renderArea->setMainWindow(this);
    ui->renderArea->setParameters(m_parameters);

    errorDisplayDialog = nullptr;
    aboutDialog = nullptr;
    languageDialog = nullptr;
    m_points = nullptr;

    setButtonColors();
    initGraphControls();
    initActions();
    initMenu();
    readSettings();
    installWidgetsEventFilter();
    widgetsConnections();
    updateLabel();
    ui->functionLineEdit->setFocus();

    if (m_parameters->intro())
        m_textToSpeech->speak(tr("Welcome to audiographs. Press F1 to open help in your browser. Press Ctrl+F12 if you don't wish to hear this message on start-up."));
}

MainWindow::~MainWindow()
{
    QDir temp = QDir::tempPath();
    QString file = temp.tempPath() + "/help.html";
    QFile::remove(file);

    writeSettings();

    delete newExpressionAction;
    delete focusExpressionAction;
    delete separatorAction;

    for (int i = 0; i < MaxRecentFiles; i++)
        delete recentFileActions[i];

    delete exitAction;

    delete startSoundButtonAction;
    delete nextAction;
    delete previousAction;
    delete sayXAction;
    delete sayYAction;
    delete sayDerivativeAction;
    delete decStepAction;
    delete incStepAction;
    delete decPrecisionAction;
    delete incPrecisionAction;
    delete previousInterestPointAction;
    delete nextInterestPointAction;
    delete nextFastAction;
    delete previousFastAction;
    delete firstPointAction;
    delete lastPointAction;
    delete selfVoiceAction;
    delete useNotesAction;
    delete useNegativeNotesAction;
    delete stopAtZeroAction;
    delete normalModeAction;
    delete firstDerivativeModeAction;
    delete secondDerivativeModeAction;
    delete showShortcutsAction;
    delete aboutAction;
    delete fileMenu;
    delete controlMenu;
    delete helpMenu;

    if (errorDisplayDialog != nullptr)
        delete errorDisplayDialog;

    if (aboutDialog != nullptr)
        delete aboutDialog;

    if (languageDialog != nullptr)
        delete languageDialog;

    delete ui;
}

void MainWindow::setButtonColors()
{
    QColor col = m_parameters->lineColor();
    QString qss = QString("background-color: %1").arg(col.name());
    ui->graphColorPushButton->setStyleSheet(qss);


    col = m_parameters->backgroundColor();
    qss = QString("background-color: %1").arg(col.name());
    ui->backgroundColorPushButton->setStyleSheet(qss);

    col = m_parameters->highlightColor();
    qss = QString("background-color: %1").arg(col.name());
    ui->highlightColorPushButton->setStyleSheet(qss);

    col = m_parameters->axesColor();
    qss = QString("background-color: %1").arg(col.name());
    ui->axesColorPushButton->setStyleSheet(qss);

    col = m_parameters->derivColor();
    qss = QString("background-color: %1").arg(col.name());
    ui->derivativeColorPushButton->setStyleSheet(qss);
}

void MainWindow::initGraphControls()
{
    ui->durationSpinBox->setValue(m_parameters->duration());
    ui->minFreqSpinBox->setValue(m_parameters->minFreq());
    ui->maxFreqSpinBox->setValue(m_parameters->maxFreq());
    ui->useNotesCheckBox->setChecked(m_parameters->useNotes());
    ui->useNegativeNotescheckBox->setChecked(m_parameters->useNegativeNotes());
    ui->stopAtZeroCheckBox->setChecked(m_parameters->stopAtZero());
    ui->selfVoiceCheckBox->setChecked(m_parameters->selfVoice());
    ui->precisionDigitsSpinBox->setValue(m_parameters->precisionDigits());
    ui->graphWidthSpinBox->setValue(m_parameters->lineWidth());
    ui->highlightSizeSpinBox->setValue(m_parameters->highlightSize());
    ui->axesSizeSpinBox->setValue(m_parameters->axesSize());
    ui->showGridCheckBox->setChecked(m_parameters->showAxes());
}

void MainWindow::initActions()
{
    newExpressionAction = new QAction(tr("New expression"), this);
    newExpressionAction->setShortcut(tr("Ctrl+N"));
    connect(newExpressionAction, &QAction::triggered, this, &MainWindow::newExpression);
    connect(newExpressionAction, &QAction::hovered, this, &MainWindow::sayWidget);

    focusExpressionAction = new QAction(tr("Edit expression"), this);
    focusExpressionAction->setShortcut(tr("Ctrl+E"));
    connect(focusExpressionAction, &QAction::triggered, this, &MainWindow::focusExpression);
    connect(focusExpressionAction, &QAction::hovered, this, &MainWindow::sayWidget);

    startSoundButtonAction = new QAction(tr("Start sound"), this);
    startSoundButtonAction->setShortcut(Qt::CTRL + Qt::Key_Space);
    connect(startSoundButtonAction, &QAction::triggered, this, &MainWindow::on_startSoundPushButton_clicked);
    connect(startSoundButtonAction, &QAction::hovered, this, &MainWindow::sayWidget);

    nextAction = new QAction(tr("Next point"), this);
    nextAction->setShortcut(Qt::Key_PageUp);
    connect(nextAction, &QAction::triggered, this, &MainWindow::on_nextPushButton_clicked);
    connect(nextAction, &QAction::hovered, this, &MainWindow::sayWidget);

    previousAction = new QAction(tr("Previous point"), this);
    previousAction->setShortcut(Qt::Key_PageDown);
    connect(previousAction, &QAction::triggered, this, &MainWindow::on_previousPushButton_clicked);
    connect(previousAction, &QAction::hovered, this, &MainWindow::sayWidget);

    sayXAction = new QAction(tr("Say X coordinate"), this);
    sayXAction->setShortcut(Qt::CTRL + Qt::Key_X);
    connect(sayXAction, &QAction::triggered, this, &MainWindow::on_xPushButton_clicked);
    connect(sayXAction, &QAction::hovered, this, &MainWindow::sayWidget);

    sayYAction = new QAction(tr("Say Y coordinate"), this);
    sayYAction->setShortcut(Qt::CTRL + Qt::Key_Y);
    connect(sayYAction, &QAction::triggered, this, &MainWindow::on_yPushButton_clicked);
    connect(sayYAction, &QAction::hovered, this, &MainWindow::sayWidget);

    sayDerivativeAction = new QAction(tr("Say derivative"), this);
    sayDerivativeAction->setShortcut(Qt::CTRL + Qt::Key_D);
    connect(sayDerivativeAction, &QAction::triggered, this, &MainWindow::on_derivativePushButton_clicked);
    connect(sayDerivativeAction, &QAction::hovered, this, &MainWindow::sayWidget);

    decStepAction = new QAction(tr("Decrease step"), this);
    decStepAction->setShortcut(tr("Ctrl+["));
    connect(decStepAction, &QAction::triggered, this, &MainWindow::on_decStepPushButton_clicked);
    connect(decStepAction, &QAction::hovered, this, &MainWindow::sayWidget);

    incStepAction = new QAction(tr("Increase step"), this);
    incStepAction->setShortcut(tr("Ctrl+]"));
    connect(incStepAction, &QAction::triggered, this, &MainWindow::on_incStepPushButton_clicked);
    connect(incStepAction, &QAction::hovered, this, &MainWindow::sayWidget);

    decPrecisionAction = new QAction(tr("Decrease precision"), this);
    decPrecisionAction->setShortcut(Qt::Key_F9);
    connect(decPrecisionAction, &QAction::triggered, this, &MainWindow::decPrecision);
    connect(decPrecisionAction, &QAction::hovered, this, &MainWindow::sayWidget);

    incPrecisionAction = new QAction(tr("Increase precision"), this);
    incPrecisionAction->setShortcut(Qt::Key_F10);
    connect(incPrecisionAction, &QAction::triggered, this, &MainWindow::incPrecision);
    connect(incPrecisionAction, &QAction::hovered, this, &MainWindow::sayWidget);

    previousInterestPointAction = new QAction(tr("Previous point of interest"), this);
    previousInterestPointAction->setShortcut(Qt::CTRL + Qt::Key_Left);
    connect(previousInterestPointAction, &QAction::triggered, this, &MainWindow::on_previousPointInterestPushButton_clicked);
    connect(previousInterestPointAction, &QAction::hovered, this, &MainWindow::sayWidget);

    nextInterestPointAction = new QAction(tr("Next point of interest"), this);
    nextInterestPointAction->setShortcut(Qt::CTRL + Qt::Key_Right);
    connect(nextInterestPointAction, &QAction::triggered, this, &MainWindow::on_nextPointInterestPushButton_clicked);
    connect(nextInterestPointAction, &QAction::hovered, this, &MainWindow::sayWidget);

    previousFastAction = new QAction(tr("Previous point (fast)"), this);
    previousFastAction->setShortcut(Qt::SHIFT + Qt::Key_Left);
    connect(previousFastAction, &QAction::triggered, this, &MainWindow::on_previousFastPushButton_clicked);
    connect(previousFastAction, &QAction::hovered, this, &MainWindow::sayWidget);

    nextFastAction = new QAction(tr("Next point (fast)"), this);
    nextFastAction->setShortcut(Qt::SHIFT + Qt::Key_Right);
    connect(nextFastAction, &QAction::triggered, this, &MainWindow::on_nextFastPushButton_clicked);
    connect(nextFastAction, &QAction::hovered, this, &MainWindow::sayWidget);

    firstPointAction = new QAction(tr("First point"), this);
    firstPointAction->setShortcut(Qt::Key_Home);
    connect(firstPointAction, &QAction::triggered, this, &MainWindow::on_firstPointPushButton_clicked);
    connect(firstPointAction, &QAction::hovered, this, &MainWindow::sayWidget);

    lastPointAction = new QAction(tr("Last point"), this);
    lastPointAction->setShortcut(Qt::Key_End);
    connect(lastPointAction, &QAction::triggered, this, &MainWindow::on_lastPointPushButton_clicked);
    connect(lastPointAction, &QAction::hovered, this, &MainWindow::sayWidget);

    selfVoiceAction = new QAction(tr("Self voice"), this);
    selfVoiceAction->setShortcut(Qt::Key_F2);
    connect(selfVoiceAction, &QAction::triggered, this, &MainWindow::selfVoiceActionActivated);
    connect(selfVoiceAction, &QAction::hovered, this, &MainWindow::sayWidget);

    useNotesAction = new QAction(tr("Use notes"), this);
    useNotesAction->setShortcut(Qt::Key_F3);
    connect(useNotesAction, &QAction::triggered, this, &MainWindow::useNotesActionActivated);
    connect(useNotesAction, &QAction::hovered, this, &MainWindow::sayWidget);

    useNegativeNotesAction = new QAction(tr("Use alternative notes for negative values"), this);
    useNegativeNotesAction->setShortcut(Qt::Key_F4);
    connect(useNegativeNotesAction, &QAction::triggered, this, &MainWindow::useNegativeNotesActionActivated);
    connect(useNegativeNotesAction, &QAction::hovered, this, &MainWindow::sayWidget);

    stopAtZeroAction = new QAction(tr("Stop sound at zero"), this);
    stopAtZeroAction->setShortcut(Qt::Key_F5);
    connect(stopAtZeroAction, &QAction::triggered, this, &MainWindow::stopAtZeroActionActivated);
    connect(stopAtZeroAction, &QAction::hovered, this, &MainWindow::sayWidget);

    languageAction = new QAction(tr("Set language"), this);
    languageAction->setShortcut(Qt::CTRL + Qt::Key_L);
    connect(languageAction, &QAction::triggered, this, &MainWindow::languageActionActivated);
    connect(languageAction, &QAction::hovered, this, &MainWindow::sayWidget);

    normalModeAction = new QAction(tr("Normal mode"), this);
    normalModeAction->setShortcut(Qt::CTRL + Qt::Key_0);
    connect(normalModeAction, &QAction::triggered, this, &MainWindow::on_normalModePushButton_clicked);
    connect(normalModeAction, &QAction::hovered, this, &MainWindow::sayWidget);

    firstDerivativeModeAction = new QAction(tr("First derivative mode"), this);
    firstDerivativeModeAction->setShortcut(Qt::CTRL + Qt::Key_1);
    connect(firstDerivativeModeAction, &QAction::triggered, this, &MainWindow::on_firstDerivativePushButton_clicked);
    connect(firstDerivativeModeAction, &QAction::hovered, this, &MainWindow::sayWidget);

    secondDerivativeModeAction = new QAction(tr("Second derivative mode"), this);
    secondDerivativeModeAction->setShortcut(Qt::CTRL + Qt::Key_2);
    connect(secondDerivativeModeAction, &QAction::triggered, this, &MainWindow::on_secondDerivativePushButton_clicked);
    connect(secondDerivativeModeAction, &QAction::hovered, this, &MainWindow::sayWidget);

    showShortcutsAction = new QAction(tr("Help"), this);
    showShortcutsAction->setShortcut(Qt::Key_F1);
    connect(showShortcutsAction, &QAction::triggered, this, &MainWindow::showShortcuts);
    connect(showShortcutsAction, &QAction::hovered, this, &MainWindow::sayWidget);

    introAction = new QAction(tr("Disable intro audio"), this);
    introAction->setShortcut(Qt::CTRL + Qt::Key_F12);
    connect(introAction, &QAction::triggered, this, &MainWindow::stopIntro);
    connect(introAction, &QAction::hovered, this, &MainWindow::sayWidget);

    aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(aboutAction, &QAction::hovered, this, &MainWindow::sayWidget);

    for (int i=0; i<MaxRecentFiles; ++i)
    {
        recentFileActions[i]=new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
        connect(recentFileActions[i], SIGNAL(hovered()), this, SLOT(sayWidget()));
    }

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    connect(exitAction, &QAction::hovered, this, &MainWindow::sayWidget);
}

void MainWindow::initMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newExpressionAction);

    for (int i=0; i<MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);

    separatorAction = fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    ui->menubar->addMenu(fileMenu);

    controlMenu = menuBar()->addMenu(tr("&Control"));
    controlMenu->addAction(startSoundButtonAction);
    controlMenu->addAction(previousAction);
    controlMenu->addAction(nextAction);
    controlMenu->addAction(sayXAction);
    controlMenu->addAction(sayYAction);
    controlMenu->addAction(sayDerivativeAction);
    controlMenu->addAction(decStepAction);
    controlMenu->addAction(incStepAction);
    controlMenu->addAction(decPrecisionAction);
    controlMenu->addAction(incPrecisionAction);
    controlMenu->addAction(previousInterestPointAction);
    controlMenu->addAction(nextInterestPointAction);
    controlMenu->addAction(previousFastAction);
    controlMenu->addAction(nextFastAction);
    controlMenu->addAction(firstPointAction);
    controlMenu->addAction(lastPointAction);
    controlMenu->addAction(selfVoiceAction);
    controlMenu->addAction(useNotesAction);
    controlMenu->addAction(useNegativeNotesAction);
    controlMenu->addAction(stopAtZeroAction);
    controlMenu->addAction(normalModeAction);
    controlMenu->addAction(firstDerivativeModeAction);
    controlMenu->addAction(secondDerivativeModeAction);
    controlMenu->addAction(focusExpressionAction);

    ui->menubar->addMenu(controlMenu);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(showShortcutsAction);
    helpMenu->addAction(introAction);
    helpMenu->addAction(languageAction);
    helpMenu->addAction(aboutAction);
    ui->menubar->addMenu(helpMenu);
}

void MainWindow::readSettings()
{
    QSettings settings("audiographs", "audiographs");
    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();
}

void MainWindow::installWidgetsEventFilter()
{
    ui->functionLineEdit->installEventFilter(this);
    ui->minXLineEdit->installEventFilter(this);
    ui->maxXLineEdit->installEventFilter(this);
    ui->minYLineEdit->installEventFilter(this);
    ui->maxYLineEdit->installEventFilter(this);
    ui->startSoundPushButton->installEventFilter(this);
    ui->helpPushButton->installEventFilter(this);
    ui->previousPushButton->installEventFilter(this);
    ui->nextPushButton->installEventFilter(this);
    ui->xPushButton->installEventFilter(this);
    ui->yPushButton->installEventFilter(this);
    ui->derivativePushButton->installEventFilter(this);
    ui->previousPointInterestPushButton->installEventFilter(this);
    ui->nextPointInterestPushButton->installEventFilter(this);
    ui->previousFastPushButton->installEventFilter(this);
    ui->nextFastPushButton->installEventFilter(this);
    ui->firstPointPushButton->installEventFilter(this);
    ui->lastPointPushButton->installEventFilter(this);
    ui->incStepPushButton->installEventFilter(this);
    ui->decStepPushButton->installEventFilter(this);
    ui->normalModePushButton->installEventFilter(this);
    ui->firstDerivativePushButton->installEventFilter(this);
    ui->secondDerivativePushButton->installEventFilter(this);
    ui->durationSpinBox->installEventFilter(this);
    ui->minFreqSpinBox->installEventFilter(this);
    ui->maxFreqSpinBox->installEventFilter(this);
    ui->precisionDigitsSpinBox->installEventFilter(this);
    ui->selfVoiceCheckBox->installEventFilter(this);
    ui->useNotesCheckBox->installEventFilter(this);
    ui->useNegativeNotescheckBox->installEventFilter(this);
    ui->stopAtZeroCheckBox->installEventFilter(this);
    ui->resetAudioPushButton->installEventFilter(this);
    ui->graphColorPushButton->installEventFilter(this);
    ui->backgroundColorPushButton->installEventFilter(this);
    ui->highlightColorPushButton->installEventFilter(this);
    ui->axesColorPushButton->installEventFilter(this);
    ui->graphWidthSpinBox->installEventFilter(this);
    ui->highlightSizeSpinBox->installEventFilter(this);
    ui->axesSizeSpinBox->installEventFilter(this);
    ui->derivativeColorPushButton->installEventFilter(this);
    ui->showGridCheckBox->installEventFilter(this);
    ui->resetGraphSettingsPushButton->installEventFilter(this);
    ui->scrollArea->installEventFilter(this);
    ui->coordLabel->installEventFilter(this);
    ui->coordLabel2->installEventFilter(this);
    this->installEventFilter(this);
}

void MainWindow::widgetsConnections()
{
    connect(ui->durationSpinBox, SIGNAL(valueChanged(int)), this, SLOT(durationSpinBoxValueChanged(int)));
    connect(ui->minFreqSpinBox, SIGNAL(valueChanged(int)), this, SLOT(minFreqSpinBoxValueChanged(int)));
    connect(ui->maxFreqSpinBox, SIGNAL(valueChanged(int)), this, SLOT(maxFreqSpinBoxValueChanged(int)));
    connect(ui->precisionDigitsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(precisionDigitsSpinboxValueChanged(int)));
    connect(ui->selfVoiceCheckBox, SIGNAL(stateChanged(int)), this, SLOT(selfVoiceCheckBoxStateChanged()));
    connect(ui->useNotesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(useNotesCheckBoxStateChanged()));
    connect(ui->useNegativeNotescheckBox, SIGNAL(stateChanged(int)), this, SLOT(useNegativeNotesCheckBoxStateChanged()));
    connect(ui->stopAtZeroCheckBox, SIGNAL(stateChanged(int)), this, SLOT(stopAtZeroCheckBoxStateChanged()));
    connect(ui->graphWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(graphWidthSpinBoxValueChanged(int)));
    connect(ui->highlightSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(highlightSizeSpinBoxValueChanged(int)));
    connect(ui->axesSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(axesSizeSpinBoxValueChanged(int)));
    connect(ui->showGridCheckBox, SIGNAL(stateChanged(int)), this, SLOT(showGridCheckBoxStateChanged()));
}

void MainWindow::updateLabel()
{
    QFont font;
    font.setPointSize(2 * m_parameters->lineWidth());

    if (font.pointSize() < 12)
        font.setPointSize(12);
    QPalette palette;

    palette.setColor(ui->coordLabel->foregroundRole(), m_parameters->lineColor());
    ui->coordLabel->setPalette(palette);
    ui->coordLabel->setFont(font);

    ui->coordLabel2->setPalette(palette);
    ui->coordLabel2->setFont(font);
}

void MainWindow::enableControls()
{
    ui->startSoundPushButton->setEnabled(true);
    ui->nextPushButton->setEnabled(true);
    nextAction->setEnabled(true);
    ui->previousPushButton->setEnabled(true);
    previousAction->setEnabled(true);
    ui->xPushButton->setEnabled(true);
    sayXAction->setEnabled(true);
    ui->yPushButton->setEnabled(true);
    sayYAction->setEnabled(true);
    ui->derivativePushButton->setEnabled(true);
    sayDerivativeAction->setEnabled(true);
    ui->decStepPushButton->setEnabled(true);
    ui->incStepPushButton->setEnabled(true);
    decStepAction->setEnabled(true);
    incStepAction->setEnabled(true);
    ui->previousPointInterestPushButton->setEnabled(true);
    ui->nextPointInterestPushButton->setEnabled(true);
    previousInterestPointAction->setEnabled(true);
    nextInterestPointAction->setEnabled(true);
    ui->previousFastPushButton->setEnabled(true);
    ui->nextFastPushButton->setEnabled(true);
    previousFastAction->setEnabled(true);
    nextFastAction->setEnabled(true);
    ui->firstPointPushButton->setEnabled(true);
    firstPointAction->setEnabled(true);
    ui->lastPointPushButton->setEnabled(true);
    lastPointAction->setEnabled(true);
    ui->normalModePushButton->setEnabled(true);
    ui->firstDerivativePushButton->setEnabled(true);
    ui->secondDerivativePushButton->setEnabled(true);
    normalModeAction->setEnabled(true);
    firstDerivativeModeAction->setEnabled(true);
    secondDerivativeModeAction->setEnabled(true);
    canZoomDrag = true;
}

void MainWindow::disableControls()
{
    ui->nextPushButton->setEnabled(false);
    nextAction->setEnabled(false);
    ui->previousPushButton->setEnabled(false);
    previousAction->setEnabled(false);
    ui->xPushButton->setEnabled(false);
    sayXAction->setEnabled(false);
    ui->yPushButton->setEnabled(false);
    sayYAction->setEnabled(false);
    ui->derivativePushButton->setEnabled(false);
    sayDerivativeAction->setEnabled(false);
    ui->decStepPushButton->setEnabled(false);
    ui->incStepPushButton->setEnabled(false);
    decStepAction->setEnabled(false);
    incStepAction->setEnabled(false);
    ui->previousPointInterestPushButton->setEnabled(false);
    ui->nextPointInterestPushButton->setEnabled(false);
    previousInterestPointAction->setEnabled(false);
    nextInterestPointAction->setEnabled(false);
    ui->previousFastPushButton->setEnabled(false);
    ui->nextFastPushButton->setEnabled(false);
    previousFastAction->setEnabled(false);
    nextFastAction->setEnabled(false);
    ui->firstPointPushButton->setEnabled(false);
    firstPointAction->setEnabled(false);
    ui->lastPointPushButton->setEnabled(false);
    lastPointAction->setEnabled(false);
    ui->normalModePushButton->setEnabled(false);
    ui->firstDerivativePushButton->setEnabled(false);
    ui->secondDerivativePushButton->setEnabled(false);
    normalModeAction->setEnabled(false);
    firstDerivativeModeAction->setEnabled(false);
    secondDerivativeModeAction->setEnabled(false);
    canZoomDrag = false;
}

void MainWindow::focusExpression()
{
    ui->functionLineEdit->setFocus();
}

void MainWindow::clearLabel()
{
    ui->coordLabel->setText("");
    ui->coordLabel2->setText("");
}

void MainWindow::stopIntro()
{
    m_parameters->setIntro(false);
}

void MainWindow::accessText(QWidget *widget, QString text)
{
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(widget->accessibleName() + " " + text);
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);

    for (int j=0; j<MaxRecentFiles; ++j)
    {
        if (j<recentFiles.count())
        {
            QString text=tr("&%1 %2").arg(j+1).arg(recentFiles[j]);
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
        {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QString expression = action->data().toString();
        ui->functionLineEdit->clear();
        ui->functionLineEdit->setText(expression);
        on_functionLineEdit_textEdited("");
        ui->functionLineEdit->setFocus();
    }
}

void MainWindow::writeSettings()
{
    QSettings settings("audiographs", "audiographs");
    settings.setValue("recentFiles", recentFiles);
}

void MainWindow::initialStateActivated()
{
    disableControls();
    ui->renderArea->clear();
    ui->renderArea->disableCurrentPoint();
    iface.setDerivativeMode(0);
}

void MainWindow::evaluateStateActivated()
{
    clearLabel();
    disableControls();
    ui->renderArea->disableCurrentPoint();
    iface.setDerivativeMode(0);
    ui->renderArea->setDerivativeMode(0);
    iface.calculate(ui->functionLineEdit->text(),
                    ui->minXLineEdit->text(),
                    ui->maxXLineEdit->text(),
                    ui->minYLineEdit->text(),
                    ui->maxYLineEdit->text());
}

void MainWindow::graphReadyStateActivated()
{
    ui->renderArea->updateGraph(m_points,
                                m_minX,
                                m_maxX,
                                m_minY,
                                m_maxY);
    enableControls();

    QString expression = ui->functionLineEdit->text();

    recentFiles.removeAll(expression);
    recentFiles.prepend(expression);
    updateRecentFileActions();
}

void MainWindow::playSoundStateActivated()
{
    ui->startSoundPushButton->setText(tr("Enter - Stop sound"));
    ui->renderArea->enableCurrentPoint();
    enableControls();
    iface.playSound();
    clearLabel();
}

void MainWindow::playSoundStateDeactivated()
{
    ui->startSoundPushButton->setText(tr("Enter - Start sound"));
    ui->renderArea->disableCurrentPoint();
    iface.stopSound();
}

void MainWindow::exploreStateActivated()
{
    ui->renderArea->enableCurrentPoint();
}

void MainWindow::exploreStateDeactivated()
{
    ui->renderArea->disableCurrentPoint();
}

void MainWindow::interestingPointStateActivated()
{
    ui->startSoundPushButton->setText(tr("Enter - Stop sound"));
    ui->renderArea->enableCurrentPoint();
}

void MainWindow::interestingPointStateDeactivated()
{
    ui->startSoundPushButton->setText(tr("Enter - Start sound"));
    iface.stopSound();
}

void MainWindow::interestingPointStoppedStateActivated()
{
    ui->startSoundPushButton->setText(tr("Enter - Start sound"));
    ui->renderArea->enableCurrentPoint();
}

void MainWindow::interestingPointStoppedStateDeactivated()
{

}

void MainWindow::newCurrentPoint(double x, double y)
{
    ui->renderArea->newCurrentPoint(x, y);
}

void MainWindow::errorDisplayStateActivated()
{
    if (errorDisplayDialog == nullptr) {
        errorDisplayDialog = new ErrorDisplayDialog(this);

        connect(errorDisplayDialog, &ErrorDisplayDialog::accepted, this, &MainWindow::errorAccepted);
        connect(errorDisplayDialog, &ErrorDisplayDialog::rejected, this, &MainWindow::errorAccepted);
    }

    errorDisplayDialog->setModal(true);

    if ( (m_parameters->language() == 2) || (m_parameters->language() == 0 && QLocale::system().name() == "el_GR") ) {
        errorDisplayDialog->setText("Σφάλμα");
        errorDisplayDialog->setWindowTitle("Σφάλμα");
    }
    else {
        errorDisplayDialog->setText(m_errorString);
        errorDisplayDialog->setWindowTitle(m_errorString);
    }
    errorDisplayDialog->show();
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(tr("Error ") + m_textToSpeech->normalizeText(m_errorString));
}

void MainWindow::updateGraph(Points *points, double minX, double maxX, double minY, double maxY)
{
    m_points = points;
    m_minX = minX;
    m_maxX = maxX;
    m_minY = minY;
    m_maxY = maxY;
    iface.newGraph();
    clearLabel();
}

void MainWindow::newInputValues(double minX, double maxX, double minY, double maxY)
{
    //we update with the rounded values
    ui->minXLineEdit->setText(QString::number(minX));
    ui->maxXLineEdit->setText(QString::number(maxX));
    ui->minYLineEdit->setText(QString::number(minY));
    ui->maxYLineEdit->setText(QString::number(maxY));
}

void MainWindow::updateDerivative(Points *points, double minX, double maxX, double minY, double maxY)
{
    m_derivPoints = points;
    m_minX = minX;
    m_maxX = maxX;
    m_minY = minY;
    m_maxY = maxY;

    ui->renderArea->updateDerivative(m_derivPoints,
                                     m_minX,
                                     m_maxX,
                                     m_minY,
                                     m_maxY);
}

void MainWindow::error(QString errorString)
{
    qDebug() << errorString;
    ui->renderArea->clear();
    clearLabel();
    m_errorString = errorString;
    iface.functionError();
}

void MainWindow::zoom(int delta)
{
    if (!canZoomDrag)
        return;

    ui->renderArea->disableCurrentPoint();
    iface.setDerivativeMode(0);
    ui->renderArea->setDerivativeMode(0);
    iface.zoom(delta);
    clearLabel();
}

void MainWindow::mousePressed(int x, int y)
{
    if (!canZoomDrag)
        return;

    m_mousePressed = true;

    //ui->renderArea->disableCurrentPoint();
    iface.setDerivativeMode(0);
    ui->renderArea->setDerivativeMode(0);
    iface.startDrag(x, y);
}

void MainWindow::mouseMove(int diffX, int diffY)
{
    if (!m_mousePressed)
        return;

    iface.drag(diffX, diffY, ui->renderArea->width(), ui->renderArea->height());
    clearLabel();
}

void MainWindow::mouseReleased()
{
    m_mousePressed = false;
}

void MainWindow::on_functionLineEdit_textEdited(const QString &arg1)
{
    Q_UNUSED(arg1);

    ui->minXLineEdit->setText("-10");
    ui->maxXLineEdit->setText("10");
    ui->minYLineEdit->setText("-10");
    ui->maxYLineEdit->setText("10");

    iface.evaluate();
}

void MainWindow::on_minXLineEdit_textEdited(const QString &arg1)
{
    accessText(ui->minXLineEdit, arg1);
    iface.evaluate();
}

void MainWindow::on_maxXLineEdit_textEdited(const QString &arg1)
{
    accessText(ui->maxXLineEdit, arg1);
    iface.evaluate();
}

void MainWindow::on_minYLineEdit_textEdited(const QString &arg1)
{
    accessText(ui->minYLineEdit, arg1);
    iface.evaluate();
}

void MainWindow::on_maxYLineEdit_textEdited(const QString &arg1)
{
    accessText(ui->maxYLineEdit, arg1);
    iface.evaluate();
}

void MainWindow::on_graphColorPushButton_clicked()
{
    const QColor color = QColorDialog::getColor(m_parameters->lineColor(), this, tr("Select Color"));

    if (color.isValid()) {
        m_parameters->setLineColor(color);
        setButtonColors();
        ui->renderArea->update();
        updateLabel();
    }
}

void MainWindow::on_backgroundColorPushButton_clicked()
{
    const QColor color = QColorDialog::getColor(m_parameters->backgroundColor(), this, tr("Select Color"));

    if (color.isValid()) {
        m_parameters->setBackgroundColor(color);
        setButtonColors();
        ui->renderArea->update();
    }
}

void MainWindow::on_highlightColorPushButton_clicked()
{
    const QColor color = QColorDialog::getColor(m_parameters->highlightColor(), this, tr("Select Color"));

    if (color.isValid()) {
        m_parameters->setHighlightColor(color);
        setButtonColors();
        ui->renderArea->update();
    }
}

void MainWindow::on_axesColorPushButton_clicked()
{
    const QColor color = QColorDialog::getColor(m_parameters->axesColor(), this, tr("Select Color"));

    if (color.isValid()) {
        m_parameters->setAxesColor(color);
        setButtonColors();
        ui->renderArea->update();
    }
}

void MainWindow::on_resetGraphSettingsPushButton_clicked()
{
    m_parameters->reset();
    setButtonColors();
    initGraphControls();
    ui->renderArea->update();
    updateLabel();
}

void MainWindow::on_startSoundPushButton_clicked()
{
    iface.playPressed();
}

void MainWindow::on_resetAudioPushButton_clicked()
{
    m_parameters->resetAudio();
    ui->durationSpinBox->setValue(m_parameters->duration());
    ui->minFreqSpinBox->setValue(m_parameters->minFreq());
    ui->maxFreqSpinBox->setValue(m_parameters->maxFreq());
    ui->useNotesCheckBox->setChecked(m_parameters->useNotes());
    ui->useNegativeNotescheckBox->setChecked(m_parameters->useNegativeNotes());
    ui->stopAtZeroCheckBox->setChecked(m_parameters->stopAtZero());
    ui->precisionDigitsSpinBox->setValue(m_parameters->precisionDigits());
}

void MainWindow::newExpression()
{
    ui->functionLineEdit->clear();
    ui->functionLineEdit->setFocus();
    ui->minXLineEdit->setText("-10");
    ui->maxXLineEdit->setText("10");
    ui->minYLineEdit->setText("-10");
    ui->maxYLineEdit->setText("10");

    iface.evaluate();
    clearLabel();
}

void MainWindow::quit()
{
    qApp->exit();
}

void MainWindow::on_nextPushButton_clicked()
{
    if (ui->nextPushButton->isEnabled()) {
        iface.nextPoint();
        clearLabel();
    }
}

void MainWindow::on_previousPushButton_clicked()
{
    if (ui->previousPushButton->isEnabled()) {
        iface.previousPoint();
        clearLabel();
    }
}

void MainWindow::on_xPushButton_clicked()
{
    if (ui->xPushButton->isEnabled()) {
        if (m_parameters->selfVoice()) {
            iface.sayX();
        }
        iface.getX();
    }
}

void MainWindow::on_yPushButton_clicked()
{
    if(ui->yPushButton->isEnabled()) {
        if (m_parameters->selfVoice()) {
            iface.sayY();
        }
        iface.getY();
    }
}

void MainWindow::on_decStepPushButton_clicked()
{
    iface.decStep();
}

void MainWindow::on_incStepPushButton_clicked()
{
    iface.incStep();
}

void MainWindow::on_previousPointInterestPushButton_clicked()
{
    if (ui->previousPointInterestPushButton->isEnabled()) {
        iface.previousPointInterest();
        clearLabel();
    }
}

void MainWindow::on_nextPointInterestPushButton_clicked()
{
    if (ui->nextPointInterestPushButton->isEnabled()) {
        iface.nextPointInterest();
        clearLabel();
    }
}
void MainWindow::on_previousFastPushButton_clicked()
{
    if(ui->previousFastPushButton->isEnabled()) {
        clearLabel();
        iface.previousFast();
    }
}

void MainWindow::on_nextFastPushButton_clicked()
{
    if(ui->nextFastPushButton->isEnabled()) {
        clearLabel();
        iface.nextFast();
    }
}

void MainWindow::on_firstPointPushButton_clicked()
{
    if (firstPointAction->isEnabled()) {
        iface.firstPoint();
        updateLabelText(tr("starting point"));
    }
}

void MainWindow::on_lastPointPushButton_clicked()
{
    if (lastPointAction->isEnabled()) {
        iface.lastPoint();
        updateLabelText(tr("ending point"));
    }
}

void MainWindow::updateLabelText(QString text)
{
    if ( (m_parameters->language() == 2) || (m_parameters->language() == 0 && QLocale::system().name() == "el_GR") )
        text.replace(".", ",");

    qDebug() << "label: " << text;
    QString oldText = ui->coordLabel->text();
    if (text != oldText) {
        ui->coordLabel2->setText("");
        ui->coordLabel->setText(text);
        if (!m_parameters->selfVoice())
            ui->coordLabel->setFocus();
    } else {
        ui->coordLabel->setText("");
        ui->coordLabel2->setText(text);
        if (!m_parameters->selfVoice())
            ui->coordLabel2->setFocus();
    }
}

void MainWindow::exit()
{
    QApplication::quit();
}

void MainWindow::errorAccepted()
{
    iface.errorAccepted();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{    
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key() == Qt::Key_Space && key->modifiers()==Qt::ControlModifier) ) {
            on_startSoundPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_Enter || key->key() == Qt::Key_Return) ) {
            on_startSoundPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_Right && key->modifiers()==Qt::ControlModifier) ) {
            on_nextPointInterestPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_Left && key->modifiers()==Qt::ControlModifier) ) {
            on_previousPointInterestPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_Right && key->modifiers()==Qt::ShiftModifier) ) {
            on_nextFastPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_Left && key->modifiers()==Qt::ShiftModifier) ) {
            on_previousFastPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_PageUp) ) {
            on_nextPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_PageDown) ) {
            on_previousPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_X && key->modifiers()==Qt::ControlModifier) ) {
            on_xPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_Y && key->modifiers()==Qt::ControlModifier) ) {
            on_yPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_D && key->modifiers()==Qt::ControlModifier) ) {
            on_derivativePushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_Home ) ) {
            on_firstPointPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_End ) ) {
            on_lastPointPushButton_clicked();
            return true;
        } else if ( (key->key() == Qt::Key_Left && (obj == ui->functionLineEdit) ) ) {
            int n = ui->functionLineEdit->cursorPosition();
            if (n == 0) {
                QString text = ui->functionLineEdit->text();
                accessText(ui->functionLineEdit, m_textToSpeech->normalizeText(text));
            }
            return false;
        } else if ( (key->key() == Qt::Key_Right && (obj == ui->functionLineEdit) ) ) {
            int n = ui->functionLineEdit->cursorPosition();
            if (n == ui->functionLineEdit->text().size()) {
                QString text = ui->functionLineEdit->text();
                accessText(ui->functionLineEdit, m_textToSpeech->normalizeText(text));
            }
            return false;
        } else if (key->key() == Qt::Key_E && key->modifiers()==Qt::ControlModifier ) {
            focusExpression();
            return true;
        }
    }

    if (event->type() == QEvent::FocusIn) {
        if (obj == ui->functionLineEdit) {
            accessText(ui->functionLineEdit, m_textToSpeech->normalizeText(ui->functionLineEdit->text()));
        } else if (obj == ui->minXLineEdit) {
            accessText(ui->minXLineEdit, ui->minXLineEdit->text());
        } else if (obj == ui->maxXLineEdit) {
            accessText(ui->maxXLineEdit, ui->maxXLineEdit->text());
        } else if (obj == ui->minYLineEdit) {
            accessText(ui->minYLineEdit, ui->minYLineEdit->text());
        } else if (obj == ui->maxYLineEdit) {
            accessText(ui->maxYLineEdit, ui->maxYLineEdit->text());
        } else if (obj == ui->durationSpinBox) {
            accessText(ui->durationSpinBox, ui->durationSpinBox->text() + " seconds");
        } else if (obj == ui->minFreqSpinBox) {
            accessText(ui->minFreqSpinBox, ui->minFreqSpinBox->text() + " hertz");
        } else if (obj == ui->maxFreqSpinBox) {
            accessText(ui->maxFreqSpinBox, ui->maxFreqSpinBox->text() + " hertz");
        } else if (obj == ui->precisionDigitsSpinBox) {
            if (ui->precisionDigitsSpinBox->value() == 1)
                accessText(ui->precisionDigitsSpinBox, ui->precisionDigitsSpinBox->text() + " digit");
            else
                accessText(ui->precisionDigitsSpinBox, ui->precisionDigitsSpinBox->text() + " digits");
        }  else if (obj == ui->selfVoiceCheckBox) {
            QString text = (ui->selfVoiceCheckBox->isChecked() ? "checked" : "not checked");
            accessText(ui->selfVoiceCheckBox, text);
        } else if (obj == ui->useNotesCheckBox) {
            QString text = (ui->useNotesCheckBox->isChecked() ? "checked" : "not checked");
            accessText(ui->useNotesCheckBox, text);
        } else if (obj == ui->useNegativeNotescheckBox) {
            QString text = (ui->useNegativeNotescheckBox->isChecked() ? "checked" : "not checked");
            accessText(ui->useNegativeNotescheckBox, text);
        } else if (obj == ui->stopAtZeroCheckBox) {
            QString text = (ui->stopAtZeroCheckBox->isChecked() ? "checked" : "not checked");
            accessText(ui->stopAtZeroCheckBox, text);
        } else if (obj == ui->graphWidthSpinBox) {
            accessText(ui->graphWidthSpinBox, ui->graphWidthSpinBox->text());
        } else if (obj == ui->highlightSizeSpinBox) {
            accessText(ui->highlightSizeSpinBox, ui->highlightSizeSpinBox->text());
        } else if (obj == ui->axesSizeSpinBox) {
            accessText(ui->axesSizeSpinBox, ui->axesSizeSpinBox->text());
        } else if (obj == ui->showGridCheckBox) {
            QString text = (ui->showGridCheckBox->isChecked() ? "checked" : "not checked");
            accessText(ui->showGridCheckBox, text);
        }
        else {
            QWidget *widget = static_cast<QWidget*>(obj);
            accessText(widget, "");
        }
    }
    return false;
}

void MainWindow::on_functionLineEdit_cursorPositionChanged(int arg1, int arg2)
{
    if (!m_parameters->selfVoice())
        return;

    Q_UNUSED(arg1);

    int n = arg2 - 1;

    QString text = ui->functionLineEdit->text();
    if (n >= 0) {
        QString t = text.mid(n, 1);
        m_textToSpeech->speak(m_textToSpeech->normalizeText(t));
    } else {
        accessText(ui->functionLineEdit, m_textToSpeech->normalizeText(text));
    }
}

void MainWindow::selfVoiceActionActivated()
{
    ui->selfVoiceCheckBox->setChecked(!ui->selfVoiceCheckBox->isChecked());
}

void MainWindow::useNotesActionActivated()
{
    ui->useNotesCheckBox->setChecked(!ui->useNotesCheckBox->isChecked());
}

void MainWindow::useNegativeNotesActionActivated()
{
    ui->useNegativeNotescheckBox->setChecked(!ui->useNegativeNotescheckBox->isChecked());
}

void MainWindow::stopAtZeroActionActivated()
{
    ui->stopAtZeroCheckBox->setChecked(!ui->stopAtZeroCheckBox->isChecked());
}

void MainWindow::languageActionActivated()
{
    if (languageDialog == nullptr)
        languageDialog = new LanguageDialog(this, m_parameters->language());
    if (languageDialog->exec())
        m_parameters->setLanguage(languageDialog->language);
}

void MainWindow::on_normalModePushButton_clicked()
{
    iface.setDerivativeMode(0);
    ui->renderArea->setDerivativeMode(0);
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(tr("Normal mode"));
    updateLabelText(tr("normal mode"));
}

void MainWindow::on_firstDerivativePushButton_clicked()
{
    iface.setDerivativeMode(1);
    ui->renderArea->setDerivativeMode(1);
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(tr("First derivative mode"));
    updateLabelText(tr("first derivative"));
}

void MainWindow::on_secondDerivativePushButton_clicked()
{
    iface.setDerivativeMode(2);
    ui->renderArea->setDerivativeMode(2);
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(tr("Second derivative mode"));
    updateLabelText(tr("second derivative"));
}

void MainWindow::durationSpinBoxValueChanged(int value)
{
    m_parameters->setDuration(value);
    accessText(ui->durationSpinBox, QString::number(value) + " seconds");
}

void MainWindow::minFreqSpinBoxValueChanged(int value)
{
    m_parameters->setMinFreq(value);
    accessText(ui->minFreqSpinBox, QString::number(value) + " hertz");
}

void MainWindow::maxFreqSpinBoxValueChanged(int value)
{
    m_parameters->setMaxFreq(value);
    accessText(ui->maxFreqSpinBox, QString::number(value) + " hertz");
}

void MainWindow::incPrecision()
{
    int value = ui->precisionDigitsSpinBox->value();
    value++;
    if (value > 5)
        value = 5;
    ui->precisionDigitsSpinBox->setValue(value);
}

void MainWindow::decPrecision()
{
    int value = ui->precisionDigitsSpinBox->value();
    value--;
    if (value < 0)
        value = 0;
    ui->precisionDigitsSpinBox->setValue(value);
}

void MainWindow::precisionDigitsSpinboxValueChanged(int value)
{
    QString text;

    m_parameters->setPrecisionDigits(value);
    if (value == 1)
        text = tr("digit");
    else
        text = tr("digits");
    accessText(ui->precisionDigitsSpinBox, QString::number(value) + " " + text);
    updateLabelText(tr("Precision ") + QString::number(value) + " " + text);
}

void MainWindow::selfVoiceCheckBoxStateChanged()
{
    bool state = ui->selfVoiceCheckBox->isChecked();

    m_parameters->setSelfVoice(state);
    if (state)
        accessText(ui->selfVoiceCheckBox, tr("checked"));
    else
        accessText(ui->selfVoiceCheckBox, tr("not checked"));
}

void MainWindow::useNotesCheckBoxStateChanged()
{
    bool state = ui->useNotesCheckBox->isChecked();

    m_parameters->setUseNotes(state);
    if (state)
        accessText(ui->useNotesCheckBox, tr("checked"));
    else
        accessText(ui->useNotesCheckBox, tr("not checked"));
}

void MainWindow::useNegativeNotesCheckBoxStateChanged()
{
    bool state = ui->useNegativeNotescheckBox->isChecked();

    m_parameters->setUseNegativeNotes(state);
    if (state)
        accessText(ui->useNegativeNotescheckBox, tr("checked"));
    else
        accessText(ui->useNegativeNotescheckBox, tr("not checked"));
}

void MainWindow::stopAtZeroCheckBoxStateChanged()
{
    bool state = ui->stopAtZeroCheckBox->isChecked();

    m_parameters->setStopAtZero(state);
    iface.stopAtZeroChanged();
    if (state)
        accessText(ui->stopAtZeroCheckBox, tr("checked"));
    else
        accessText(ui->stopAtZeroCheckBox, tr("not checked"));
}

void MainWindow::graphWidthSpinBoxValueChanged(int value)
{
    m_parameters->setLineWidth(value);
    ui->renderArea->update();
    updateLabel();
    accessText(ui->graphWidthSpinBox, QString::number(value));
}

void MainWindow::highlightSizeSpinBoxValueChanged(int value)
{
    m_parameters->setHighlightSize(value);
    ui->renderArea->update();
    accessText(ui->highlightSizeSpinBox, QString::number(value));
}

void MainWindow::axesSizeSpinBoxValueChanged(int value)
{
    m_parameters->setAxesSize(value);
    ui->renderArea->update();
    accessText(ui->axesSizeSpinBox, QString::number(value));
}

void MainWindow::showGridCheckBoxStateChanged()
{
    bool state = ui->showGridCheckBox->isChecked();

    m_parameters->setShowAxes(state);
    ui->renderArea->update();

    if (state)
        accessText(ui->showGridCheckBox, tr("checked"));
    else
        accessText(ui->showGridCheckBox, tr("not checked"));
}

void MainWindow::on_derivativeColorPushButton_clicked()
{
    const QColor color = QColorDialog::getColor(m_parameters->derivColor(), this, tr("Select Color"));

    if (color.isValid()) {
        m_parameters->setDerivColor(color);
        setButtonColors();
        ui->renderArea->update();
    }
}

void MainWindow::showShortcuts()
{
    QString filename;
    if (m_parameters->language() == 1) {

        filename = "C:/Program Files/Audiographs/doc/doc.html";

        if ( !QFile::exists(filename)) {
            filename = "C:/Program Files (x86)/Audiographs/doc/doc.html";
        }
    } else if (m_parameters->language() == 2) {
        filename = "C:/Program Files/Audiographs/doc/doc_GR.html";

        if ( !QFile::exists(filename)) {
            filename = "C:/Program Files (x86)/Audiographs/doc/doc_GR.html";
        }
    } else if (m_parameters->language() == 0) {
        if (QLocale::system().name() == "el_GR") {
            filename = "C:/Program Files/Audiographs/doc/doc_GR.html";

            if ( !QFile::exists(filename)) {
                filename = "C:/Program Files (x86)/Audiographs/doc/doc_GR.html";
            }
        } else {
            filename = "C:/Program Files/Audiographs/doc/doc.html";

            if ( !QFile::exists(filename)) {
                filename = "C:/Program Files (x86)/Audiographs/doc/doc.html";
            }
        }
    }

    QUrl url = QUrl::fromLocalFile(filename);
    QDesktopServices::openUrl(url);
}

void MainWindow::showAboutDialog()
{
    if (aboutDialog == nullptr) {
        aboutDialog = new AboutDialog();
        connect(aboutDialog, &AboutDialog::accepted, this, &MainWindow::closeAboutDialog);
        connect(aboutDialog, &AboutDialog::rejected, this, &MainWindow::closeAboutDialog);
    }

    QString text = tr("Audiographs version 0.5\nemail: nstrikos@yahoo.gr");
    aboutDialog->setWindowTitle(tr("About"));
    aboutDialog->setModal(true);
    aboutDialog->setText(text);
    aboutDialog->show();
    m_textToSpeech->speak(text);
}

void MainWindow::closeAboutDialog()
{
    aboutDialog->hide();
    m_textToSpeech->stop();
}

void MainWindow::sayWidget()
{
    if(!m_parameters->selfVoice())
        return;

    QObject *sender = QObject::sender();

    QAction *action = static_cast<QAction*> (sender);
    QString text = action->text();
    text = text.replace("&", "");
    text = m_textToSpeech->normalizeText(text);
    m_textToSpeech->speak(text);
}

void MainWindow::on_derivativePushButton_clicked()
{
    if (ui->derivativePushButton->isEnabled()) {
        if (m_parameters->selfVoice()) {
            iface.sayDerivative();
        }
        iface.getDerivative();
    }
}

void MainWindow::on_useNotesCheckBox_toggled(bool checked)
{
    Q_UNUSED(checked);
    if (!m_parameters->selfVoice())
        ui->useNotesCheckBox->setFocus();
}

void MainWindow::on_selfVoiceCheckBox_toggled(bool checked)
{
    Q_UNUSED(checked);
    if (!m_parameters->selfVoice())
        ui->selfVoiceCheckBox->setFocus();
}

void MainWindow::on_useNegativeNotescheckBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if (!m_parameters->selfVoice())
        ui->useNegativeNotescheckBox->setFocus();
}

void MainWindow::on_stopAtZeroCheckBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if (!m_parameters->selfVoice())
        ui->stopAtZeroCheckBox->setFocus();
}

