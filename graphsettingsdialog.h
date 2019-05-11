#ifndef GRAPHSETTINGSDIALOG_H
#define GRAPHSETTINGSDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <parameters.h>

namespace Ui {
class GraphSettingsDialog;
}

class GraphSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GraphSettingsDialog(QWidget *parent = nullptr);
    ~GraphSettingsDialog();
    void setParameters(Parameters *parameters);
private slots:
    void on_pointsColorButton_clicked();
    void on_lineColorButton_clicked();
    void on_restorePushButton_clicked();
    void on_pointsSizeSpinBox_valueChanged(int arg1);
    void on_lineWidthSpinBox_valueChanged(int arg1);
    void on_backgroundButton_clicked();
    void on_highlightlButton_clicked();
    void on_highlightBox_valueChanged(int arg1);

    void on_showPointsCheckBox_clicked();

    void on_showLineCheckBox_clicked();

    void on_axesColorButton_clicked();

    void on_axesSizeSpinBox_valueChanged(int arg1);

    void on_showAxesCheckBox_clicked();

private:
    Ui::GraphSettingsDialog *ui;
    Parameters *m_parameters;
    void update();
};

#endif // GRAPHSETTINGSDIALOG_H
