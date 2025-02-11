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

#include "mainWindow.h"
#include <QTranslator>
#include "aboutDialog.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    optionWidget_ = new OptionWidget();
    trayIcon_     = new QSystemTrayIcon(QIcon(":/img/image/main_icon.png"), this);
    menuTrayIcon_ = new MenuTrayIcon();
    translator_   = new QTranslator(this);
    settings_     = new QSettings("settings.ini", QSettings::IniFormat);

    init();
    signalsProcess();
}

MainWindow::~MainWindow() {
    delete optionWidget_;
    delete trayIcon_;
    delete ui;
    delete menuTrayIcon_;
    delete translator_;
    delete settings_;
}

void MainWindow::init() {
    this->setWindowTitle(tr("Windows Auto Shutdown By CodingRookie"));
    trayIcon_->setContextMenu(menuTrayIcon_);
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

    connect(menuTrayIcon_, &MenuTrayIcon::sigExit, [] {
        QApplication::exit(0);
    });
    connect(menuTrayIcon_, &MenuTrayIcon::sigShowMainWindow, [&] {
        if (this->isMinimized()) {
            this->showNormal();
        } else if (this->isHidden()) {
            this->show();
        }
    });

    connect(ui->action_zh_CN, &QAction::triggered, [&] {
        ChangeLanguage(Language::zh_CN);
    });

    connect(ui->action_en_US, &QAction::triggered, [&] {
        ChangeLanguage(Language::en_US);
    });
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // 重写关闭事件，将窗口最小化到系统托盘
    this->hide();
    event->ignore();
}

bool MainWindow::event(QEvent *event) {
    return QMainWindow::event(event);
}

void MainWindow::RestartApp() {
    // 获取当前程序的路径和参数
    const QString program       = QApplication::applicationFilePath();
    const QStringList arguments = QApplication::arguments();

    // 启动一个新的程序实例
    QProcess::startDetached(program, arguments);

    // 退出当前程序
    QApplication::quit();
}

void MainWindow::ChangeLanguage(const Language &language) {
    QMessageBox message_box;
    message_box.setText(tr("Restart the program to apply the language change?"));
    message_box.addButton(QMessageBox::StandardButtons::enum_type::Yes);
    message_box.addButton(QMessageBox::StandardButtons::enum_type::No);
    message_box.setDefaultButton(QMessageBox::StandardButtons::enum_type::Yes);
    message_box.setModal(true);
    connect(&message_box, &QMessageBox::buttonClicked, [&](QAbstractButton *button) {
        QMessageBox::StandardButton standard_button = message_box.standardButton(button);
        if (standard_button == QMessageBox::StandardButton::Yes) {
            switch (language) {
            case Language::zh_CN:
                settings_->setValue("language", "zh_CN");
                break;
            case Language::en_US:
                settings_->setValue("language", "en_US");
                break;
            default:
                break;
            }
            settings_->sync();
            RestartApp();
        } else {
            message_box.close();
        }
    });

    message_box.exec();
}
