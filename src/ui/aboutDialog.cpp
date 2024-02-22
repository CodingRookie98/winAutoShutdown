/**
 ******************************************************************************
 * @file           : aboutDialog.cpp
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/22
 ******************************************************************************
 */

// You may need to build the project (run Qt uic code generator) to get "ui_AboutDialog.h" resolved

#include "aboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AboutDialog) {
    ui->setupUi(this);
    
    init();
    signalsProcess();
}

AboutDialog::~AboutDialog() {
    delete ui;
}
void AboutDialog::signalsProcess() {
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &QDialog::close);
}
void AboutDialog::init() {
    ui->textBrowser->setSource(QUrl("qrc:/markdown/About.md"), QTextDocument::HtmlResource);
}
