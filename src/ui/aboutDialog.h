/**
 ******************************************************************************
 * @file           : aboutDialog.h
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/22
 ******************************************************************************
 */

#ifndef WINAUTOSHUTDOWN_SRC_UI_ABOUTDIALOG_H_
#define WINAUTOSHUTDOWN_SRC_UI_ABOUTDIALOG_H_

#include <QWidget>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AboutDialog;
}
QT_END_NAMESPACE

class AboutDialog : public QDialog {
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog() override;

protected:
    bool event(QEvent *event) override;

private:
    Ui::AboutDialog *ui;
    
    void init();
    void signalsProcess();
};

#endif // WINAUTOSHUTDOWN_SRC_UI_ABOUTDIALOG_H_
