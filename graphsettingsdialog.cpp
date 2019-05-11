#include "graphsettingsdialog.h"
#include "ui_graphsettingsdialog.h"

GraphSettingsDialog::GraphSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphSettingsDialog)
{
    ui->setupUi(this);
}

GraphSettingsDialog::~GraphSettingsDialog()
{
    delete ui;
}

void GraphSettingsDialog::on_pointsColorButton_clicked()
{
    QColor color = QColorDialog::getColor(m_parameters->pointColor());
    if (color.isValid()) {
        m_parameters->setPointColor(color);
        update();
    }
}

void GraphSettingsDialog::on_pointsSizeSpinBox_valueChanged(int arg1)
{
    m_parameters->setPointSize(arg1);
    update();
}

void GraphSettingsDialog::on_lineColorButton_clicked()
{
    QColor color = QColorDialog::getColor(m_parameters->lineColor());
    if (color.isValid()) {
        m_parameters->setLineColor(color);
        update();
    }
}

void GraphSettingsDialog::on_lineWidthSpinBox_valueChanged(int arg1)
{
    m_parameters->setLineWidth(arg1);
    update();
}

void GraphSettingsDialog::on_backgroundButton_clicked()
{
    QColor color = QColorDialog::getColor(m_parameters->backgroundColor());
    if (color.isValid()) {
        m_parameters->setBackgroundColor(color);
        update();
    }
}

void GraphSettingsDialog::on_highlightlButton_clicked()
{
    QColor color = QColorDialog::getColor(m_parameters->highlightColor());
    if (color.isValid()) {
        m_parameters->setHighlightColor(color);
        update();
    }
}

void GraphSettingsDialog::on_highlightBox_valueChanged(int arg1)
{
    m_parameters->setHighlightSize(arg1);
    update();
}

void GraphSettingsDialog::on_axesColorButton_clicked()
{
    QColor color = QColorDialog::getColor(m_parameters->axesColor());
    if (color.isValid()) {
        m_parameters->setAxesColor(color);
        update();
    }
}

void GraphSettingsDialog::on_axesSizeSpinBox_valueChanged(int arg1)
{
    m_parameters->setAxesSize(arg1);
    update();
}

void GraphSettingsDialog::on_showPointsCheckBox_clicked()
{
    m_parameters->setShowPoints(ui->showPointsCheckBox->isChecked());
}

void GraphSettingsDialog::on_showLineCheckBox_clicked()
{
    m_parameters->setShowLine(ui->showLineCheckBox->isChecked());
}

void GraphSettingsDialog::on_showAxesCheckBox_clicked()
{
    m_parameters->setShowAxes(ui->showAxesCheckBox->isChecked());
}

void GraphSettingsDialog::on_restorePushButton_clicked()
{
    m_parameters->reset();
    update();
}

void GraphSettingsDialog::setParameters(Parameters *parameters)
{
    m_parameters = parameters;
    update();
}

void GraphSettingsDialog::update()
{
    QPixmap px(50, 50);
    px.fill(m_parameters->pointColor());
    ui->pointsColorButton->setIcon(px);

    ui->pointsSizeSpinBox->setValue(m_parameters->pointSize());

    px.fill(m_parameters->lineColor());
    ui->lineColorButton->setIcon(px);

    ui->lineWidthSpinBox->setValue(m_parameters->lineWidth());

    px.fill(m_parameters->backgroundColor());
    ui->backgroundButton->setIcon(px);

    px.fill(m_parameters->highlightColor());
    ui->highlightlButton->setIcon(px);

    ui->highlightBox->setValue(m_parameters->highlightSize());

    px.fill(m_parameters->axesColor());
    ui->axesColorButton->setIcon(px);

    ui->axesSizeSpinBox->setValue(m_parameters->axesSize());

    ui->showPointsCheckBox->setChecked(m_parameters->showPoints());

    ui->showLineCheckBox->setChecked(m_parameters->showLine());

    ui->showAxesCheckBox->setChecked(m_parameters->showAxes());
}
