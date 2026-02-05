/**
 ******************************************************************************
 * @file           : mainWindow.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/18
 ******************************************************************************
 */

#ifndef WINAUTOSHUTDOWN_SRC_MAINWINDOW_H_
#define WINAUTOSHUTDOWN_SRC_MAINWINDOW_H_

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QSettings>
#include "optionWidget.h"
#include "menuTrayIcon.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class Language {
    en_US,
    zh_CN,
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void init();

protected:
    void closeEvent(QCloseEvent *event) override;
    bool event(QEvent *event) override;

private:
    Ui::MainWindow *ui;
    OptionWidget *optionWidget_;
    QSystemTrayIcon *trayIcon_;
    MenuTrayIcon *menuTrayIcon_;
    QTranslator *translator_;
    QSettings *settings_;

    void signalsProcess();
    static void RestartApp();
    void ChangeLanguage(const Language &language);
};

#endif // WINAUTOSHUTDOWN_SRC_MAINWINDOW_H_
