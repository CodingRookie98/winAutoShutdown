/**
 ******************************************************************************
 * @file           : mainWindow.cpp
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/18
 ******************************************************************************
 */

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QMessageBox>
#include "mainWindow.h"
#include "aboutDialog.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    optionWidget_ = new OptionWidget();
    trayIcon_     = new QSystemTrayIcon(QIcon(":/img/image/main_icon.png"), this);
    menuTrayIcon  = new MenuTrayIcon();

    init();
    signalsProcess();
}

MainWindow::~MainWindow() {
    delete trayIcon_;
    delete optionWidget_;
    delete ui;
}

void MainWindow::init() {
    this->setWindowTitle(tr("Windows Auto Shutdown By CodingRookie"));
    trayIcon_->setContextMenu(menuTrayIcon);
    trayIcon_->show();
}

void MainWindow::signalsProcess() {
    connect(ui->actionAbout, &QAction::triggered, [&]() {
        AboutDialog aboutDialog(this);
        aboutDialog.setModal(true);
        aboutDialog.exec();
    });

    // 双击系统托盘显示主界面
    connect(trayIcon_, &QSystemTrayIcon::activated, [&](const QSystemTrayIcon::ActivationReason &reason) {
        if (reason == QSystemTrayIcon::ActivationReason::DoubleClick) {
            if (this->isMinimized()) {
                this->showNormal();
            } else if (this->isHidden()) {
                this->show();
            }
        }
    });

    connect(menuTrayIcon, &MenuTrayIcon::sigExit, [] {
        QApplication::exit(0);
    });
    connect(menuTrayIcon, &MenuTrayIcon::sigShowMainWindow, [&] {
        if (this->isMinimized()) {
            this->showNormal();
        } else if (this->isHidden()) {
            this->show();
        }
    });
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox messageBox(this);
    messageBox.setText("是否最小化到系统托盘");
    auto btnYes = messageBox.addButton("是", QMessageBox::ButtonRole::YesRole);
    auto btnNo  = messageBox.addButton("否", QMessageBox::ButtonRole::NoRole);
    messageBox.setModal(true);
    connect(btnYes, &QAbstractButton::clicked, [&] {
        // 重写关闭事件，将窗口最小化到系统托盘
        this->hide();
        event->ignore();
    });
    connect(btnNo, &QAbstractButton::clicked, [&] {
        QApplication::exit(0);
    });
    messageBox.exec();
}