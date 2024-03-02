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
#include <QMenu>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include "optionWidget.h"
#include "menuTrayIcon.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void init();
    
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    OptionWidget *optionWidget_;
    QSystemTrayIcon *trayIcon_;
    MenuTrayIcon *menuTrayIcon;

        void
        signalsProcess();
};

#endif // WINAUTOSHUTDOWN_SRC_MAINWINDOW_H_
