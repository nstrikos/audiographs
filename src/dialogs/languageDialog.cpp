#include "languageDialog.h"
#include "ui_languageDialog.h"

LanguageDialog::LanguageDialog(QWidget *parent, int language) :
    QDialog(parent),
    ui(new Ui::languageDialog)
{
    ui->setupUi(this);
    if (language == 0)
        ui->radioButton->setChecked(true);
    else if (language == 1)
        ui->radioButton_2->setChecked(true);
    else if (language == 2)
        ui->radioButton_3->setChecked(true);
}

LanguageDialog::~LanguageDialog()
{
    delete ui;
}

void LanguageDialog::on_languageDialog_accepted()
{
    if (ui->radioButton->isChecked())
        language = 0;
    else if (ui->radioButton_2->isChecked())
        language = 1;
    else if (ui->radioButton_3->isChecked())
        language = 2;
}

