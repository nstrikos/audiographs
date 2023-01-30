#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QDialog>

namespace Ui {
class languageDialog;
}

class LanguageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LanguageDialog(QWidget *parent = nullptr, int language = 0);
    ~LanguageDialog();
    int language;

private slots:
    void on_languageDialog_accepted();

private:
    Ui::languageDialog *ui;
};

#endif // LANGUAGEDIALOG_H
