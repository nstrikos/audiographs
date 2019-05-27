#include "appwindow.h"
#include "ui_appwindow.h"

#include <QDebug>

AppWindow::AppWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppWindow)
{
    ui->setupUi(this);
    initUi();
    initVariables();
    readSettings();
    connectSignals();
}

AppWindow::~AppWindow()
{
    saveSettings();

    delete m_parameters;
    delete m_audioPoints;

    if (graphSettingsDialog != nullptr)
        delete graphSettingsDialog;

    if (audioEngine != nullptr)
        delete audioEngine;
    delete ui;
}

void AppWindow::initUi()
{
    this->setWindowTitle(tr("Audio graphs"));
}

void AppWindow::initVariables()
{
    audioEngine = nullptr;
    graphSettingsDialog = nullptr;
    m_audioPoints = new AudioPoints();
    m_parameters = new Parameters();
    ui->renderArea->setParameters(m_parameters);
    m_curPoint = -1;
}

void AppWindow::connectSignals()
{
    connect(ui->drawButton, SIGNAL(clicked()), this, SLOT(drawButtonClicked()));

    //connect(ui->pointsCheckBox, SIGNAL(clicked(bool)), this, SLOT(pointsCheckBoxClicked()));
    //connect(ui->lineCheckBox, SIGNAL(clicked(bool)), this, SLOT(lineCheckBoxClicked()));

    //To check
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopButtonClicked()));
}

void AppWindow::setFunction(Function *function)
{
    m_function = function;
    connect(m_function, SIGNAL(error(QString)), this, SLOT(error(QString)));
    connect(m_function, SIGNAL(update()), this, SLOT(draw()));
}

void AppWindow::resizeEvent(QResizeEvent *event)
{
    ui->renderArea->updateGraph(m_function);
}

void AppWindow::readSettings()
{
    QSettings settings("audiographs", "audiographs");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int screenHeight = screenGeometry.height();
    int screenWidth = screenGeometry.width();

    QPoint pos = settings.value("windowPosition", QPoint(0, 0)).toPoint();
    QSize size = settings.value("windowSize", QSize(screenWidth, screenHeight)).toSize();

    resize(size);
    move(pos);
}

void AppWindow::saveSettings()
{
    QSettings settings("audiographs", "audiographs");

    settings.setValue("windowPosition", pos());
    settings.setValue("windowSize", size());
}

void AppWindow::resetAudioEngine()
{
    qDebug() << "Trying to delete audio engine";
    if (audioEngine != NULL)
    {
        audioEngine->stop();
        delete audioEngine;
        audioEngine = NULL;
    }
}

void AppWindow::drawButtonClicked()
{
    FunctionInput functionInput;

    functionInput.expression = ui->functionEdit->text();
    functionInput.minimum = ui->minimumEdit->text();
    functionInput.maximum = ui->maximumEdit->text();
    functionInput.numPoints = ui->numPointsEdit->text();

    //emit calcPoints(functionInput);//
    m_function->calculate(functionInput);
}

void AppWindow::draw()
{
    ui->renderArea->updateGraph(m_function);
}

void AppWindow::error(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}

void AppWindow::startButtonClicked()
{
    drawButtonClicked();
    //change this to signal
    resetAudioEngine();

    qDebug() << "Trying to create audio output";
    int seconds = ui->timeBox->value();
    int fmin = ui->minFreqBox->value();
    int fmax = ui->maxFreqBox->value();
    QString expression = ui->functionEdit->text();
    double start = ui->minimumEdit->text().toDouble();
    double end = ui->maximumEdit->text().toDouble();
    audioEngine = new AudioEngine(expression, start, end, seconds, fmin, fmax);
    audioEngine->createAudioOutput();
    //ui->renderArea->startTimer(ui->timeBox->value());
    ui->renderArea->startPoints(ui->timeBox->text());
}

void AppWindow::stopButtonClicked()
{
    qDebug() << "Trying to stop audio engine";
    //change this to signal
    if (audioEngine != NULL)
        audioEngine->stop();
}

void AppWindow::on_actionGraph_settings_triggered()
{
    if (graphSettingsDialog == nullptr) {
        graphSettingsDialog = new GraphSettingsDialog(this);
        graphSettingsDialog->setParameters(m_parameters);
    }

    if (graphSettingsDialog->exec()) {
        ui->renderArea->setParameters(m_parameters);
        ui->renderArea->update();
    }
}

void AppWindow::keyPressEvent(QKeyEvent *ev)
{
    if (ev->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(ev);
        if ( key->key()==Qt::Key_F4) {
            m_audioPoints->startAudio();
            ui->renderArea->startPoints(ui->timeBox->text());
        }
        else if ( key->key()==Qt::Key_F5) {
            m_audioPoints->stopAudio();
        }
        else if ( key->key()==Qt::Key_F8) {
            previousPoint();
        } else if (key->key() == Qt::Key_F9) {
            nextPoint();
        }
    }
}

void AppWindow::nextPoint()
{
    m_curPoint++;
    setAudioPointsFreq();
    //    m_audioPoints->setFreq(0);
    ui->renderArea->nextPoint();
}

void AppWindow::previousPoint()
{
    m_curPoint--;
    setAudioPointsFreq();
    ui->renderArea->previousPoint();
    //    m_audioPoints->setFreq2(0);
}

void AppWindow::setAudioPointsFreq()
{
    qDebug() << m_curPoint;
    if (audioEngine != nullptr) {
        if (m_curPoint < 0 ) {
            m_curPoint = -1;
            m_audioPoints->stopAudio();
            //ui->renderArea->setShowHighlightPoint(false);
            return;
        }
        if (m_curPoint >= m_function->size()) {
            m_curPoint = m_function->size();
            m_audioPoints->stopAudio();
            //ui->renderArea->setShowHighlightPoint(false);
            return;
        }

        m_yMin = m_function->y(0);
        m_yMax = m_yMin;
        for (int i = 0; i < m_function->size(); i++) {
            double y = m_function->y(i);
            if (y > m_yMax)
                m_yMax = y;
            if (y < m_yMin)
                m_yMin = y;
        }

        int fmin = audioEngine->getFmin();
        int fmax = audioEngine->getFmax();
        double y = m_function->y(m_curPoint);
        qDebug() << "y: " << y;
        double a = (double) (fmax-fmin)/(m_yMax - m_yMin);
        qDebug() << m_yMax << " " << m_yMin << " " << a;
        double b = fmax - a * m_yMax;
        double f = a * y + b;
        double freq = f;
        qDebug() << freq;
#ifndef Q_OS_ANDROID
        //        freq = round( f / 25.0) * 25;
#else
        //        freq = round( f / 100.0) * 100;
#endif
        m_audioPoints->setFreq(freq);
        //ui->renderArea->setCurrentPoint(m_curPoint);
        //ui->renderArea->setShowHighlightPoint(true);
        //ui->renderArea->update();
    }
}
